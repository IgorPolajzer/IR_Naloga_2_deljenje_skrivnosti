#include <cmath>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Check_Button.H>
#include <boost/multiprecision/cpp_int.hpp>
#include <stdexcept>
#include <FL/Fl_File_Chooser.H>

#include "file_utils.h"

using boost::multiprecision::cpp_int;
using boost::multiprecision::cpp_rational;
using namespace std;

// Global GUI components
Fl_Input *secret_input;
Fl_Input *k_input;
Fl_Input *n_input;
Fl_Input *file_parts_prefix_input;
Fl_Check_Button *basic_reconstruct_button;
Fl_Check_Button *robust_reconstruct_button;
Fl_Text_Buffer *output_buffer;
Fl_Text_Display *output_display;
Fl_File_Chooser *input_file_chooser;

cpp_int polynomial(const vector<cpp_int> &a, const cpp_int &k, const cpp_int &x) {
    cpp_int result = 0;

    for (int i = 0; i < k; i++) {
        result += a[i] * boost::multiprecision::pow(x, i);
    }

    return result;
}

void divide_secret_button(Fl_Widget *widget, void *data) {
    try {
        const cpp_int input_secret = stoull(secret_input->value());
        const cpp_int k = stoull(k_input->value());
        const cpp_int n = stoull(n_input->value());
        cpp_int secret;

        if (input_file_chooser->value()) {
            secret = read_file_as_int(input_file_chooser->value());
        } else {
            secret = input_secret;
        }
        cpp_int val = secret;
        val <<= 256;
        cout << "Provided int: " << val.str() << endl;

        vector<cpp_int> a;
        vector<pair<cpp_int, cpp_int>> D;

        // a0 = secret message.
        a.emplace_back(secret);

        // For testing.
        a.emplace_back(166);
        a.emplace_back(94);

        string entryOutput;

        for (int i = 1; i <= n; i++) {
            auto entry = pair(i, polynomial(a, k, i));
            D.emplace_back(entry);
            entryOutput += "D<" + boost::lexical_cast<string>(entry.first)
                    + "," + boost::lexical_cast<string>(entry.second) + ">";

            // Write D[i] to file
            filesystem::create_directories("divided_files");
            ofstream outfile(
                "divided_files/" + boost::lexical_cast<string>(file_parts_prefix_input->value()) + "_" + boost::lexical_cast<
                    string>(i) + ".txt");
            outfile << boost::lexical_cast<string>(entry.first) + ";" + boost::lexical_cast<string>(entry.second);
        }

        if (input_file_chooser->value()) entryOutput = "File divided";
        output_buffer->text(entryOutput.c_str());
    } catch (const exception &e) {
        output_buffer->text("Error: Invalid input values");
    }
}

cpp_rational reconstruct_secret_basic(const vector<pair<cpp_int, cpp_int> > &D, const cpp_int &k) {
    cpp_rational secret;

    if (k > D.size()) throw invalid_argument("K is larger than the size of provided D.");

    for (int j = 0; j < k; j++) {
        cpp_rational product = 1;
        for (int i = 0; i < k; i++) {
            if (i == j) continue;

            product *= cpp_rational(D[i].first, (D[i].first - D[j].first)); // Division
        }
        secret += D[j].second * product;
    }

    return secret;
}

cpp_rational reconstruct_secret_robust(const vector<pair<cpp_int, cpp_int> > &D, const cpp_int &k) {
    if (k > D.size()) throw invalid_argument("K is larger than the size of provided D.");

    cpp_int down_global = 1;

    for (int j = 0; j < k; j++) {
        cpp_int product = 1;
        for (int i = 0; i < k; i++) {
            if (i == j) continue;
            product *= D[i].first - D[j].first;
        }

        down_global *= product;
    }

    cpp_int secret = 0;

    for (int j = 0; j < k; j++) {
        cpp_int up = 1;
        cpp_int down_local = 1;

        for (int i = 0; i < k; i++) {
            if (i == j) continue;
            up *= D[i].first;
        }

        for (int i = 0; i < k; i++) {
            if (i == j) continue;
            down_local *= D[i].first - D[j].first;
        }

        secret += D[j].second * up * (down_global / down_local);
    }
    secret /= down_global;

    return secret;
}

void reconstruct_secret_button(Fl_Widget *widget, void *data) {
    try {
        const cpp_int k = stoull(k_input->value());
        const vector<pair<cpp_int, cpp_int>> D = read_parts_to_vector();
        /*{
            {1, 1494},
            {2, 1942},
            {3, 2578},
            {4, 3402},
            {5, 4414},
            {6, 5614}
        };*/

        cpp_rational secret;

        if (basic_reconstruct_button->value() && robust_reconstruct_button->value()) {
            output_buffer->text("You can only choose one reconstruction mode.");
            return;
        }

        if (basic_reconstruct_button->value()) {
            secret = reconstruct_secret_basic(D, k);
        } else if (robust_reconstruct_button->value()) {
            secret = reconstruct_secret_robust(D, k);
        } else {
            output_buffer->text("Please choose one reconstruction mode.");
            return;
        }

        cpp_int val = cpp_int(secret);
        val <<= 256;
        cout << "Reconstructed int: " << val.str() << endl;
        write_int_as_file(cpp_int(secret));
        output_buffer->text("File reconstructed.");
    } catch (const exception &e) {
        output_buffer->text("Error: Invalid input values");
    }
}

int main() {
    auto *window = new Fl_Window(600, 600, "Secret Sharing");

    // Title
    auto *title = new Fl_Box(20, 10, 560, 30, "Manage Secrets");
    title->labelsize(16);
    title->labelfont(FL_BOLD);

    // File Choosers
    input_file_chooser = new Fl_File_Chooser(".", "*", Fl_File_Chooser::SINGLE, "Choose Secret File");

    // Input fields
    auto *secret_label = new Fl_Box(20, 50, 100, 30, "Secret:");
    secret_label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    secret_input = new Fl_Input(130, 50, 450, 30);
    secret_input->value("1234");

    auto *n_label = new Fl_Box(20, 90, 100, 30, "N:");
    n_label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    n_input = new Fl_Input(130, 90, 450, 30);
    n_input->value("6");

    auto *k_label = new Fl_Box(20, 130, 100, 30, "K:");
    k_label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    k_input = new Fl_Input(130, 130, 450, 30);
    k_input->value("3");

    auto *file_parts_prefix_label = new Fl_Box(20, 130, 100, 30, "K:");
    file_parts_prefix_label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    file_parts_prefix_input = new Fl_Input(130, 170, 450, 30);
    file_parts_prefix_input->value("file_part");

    // Buttons
    auto *choose_file_button = new Fl_Button(25, 210, 150, 40, "Choose Secret File");
    choose_file_button->callback([](Fl_Widget *, void *) { open_file_dialog(*input_file_chooser); });

    auto *divide_btn = new Fl_Button(225, 210, 150, 40, "Divide Secret");
    divide_btn->callback(divide_secret_button);

    auto *reconstruct_btn = new Fl_Button(425, 210, 150, 40, "Reconstruct Secret");
    reconstruct_btn->callback(reconstruct_secret_button);

    // Choose reconstruction option
    basic_reconstruct_button = new Fl_Check_Button(125, 270, 100, 25, "Basic");
    robust_reconstruct_button = new Fl_Check_Button(325, 270, 100, 25, "Robust");

    // Output text buffer
    output_buffer = new Fl_Text_Buffer();
    output_display = new Fl_Text_Display(20, 340, 560, 230);
    output_display->buffer(output_buffer);

    window->end();
    window->show();

    return Fl::run();
}
