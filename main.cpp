#include <iostream>
#include <vector>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include "lcg.h"

using namespace std;

// Global GUI components
Fl_Input *secret_input;
Fl_Input *k_input;
Fl_Input *n_input;
/*Fl_Input *seed_input;
Fl_Input *min_input;
Fl_Input *max_input;
Fl_Input *count_input;
*/
Fl_Text_Buffer *output_buffer;
Fl_Text_Display *output_display;

int evaluatePolynomial(const std::vector<int>& coeffs, int x) {
    int result = 0.0;
    int power = 1.0;

    for (int coef : coeffs) {
        result += coef * power;
        power *= x;
    }

    return result;
}

void divide_secret(Fl_Widget* widget, void* data) {
    try {
        const uint64_t secret = stoull(secret_input->value());
        const uint64_t k = stoull(k_input->value());
        const uint64_t n = stoull(n_input->value());

        vector<int> a;
        vector<int> D;

        // a0 = secret message.
        a.emplace_back(secret);

        // Generate coeficients.
        /*for (int i = 0; i < k - 1; i++) {
            vector<int> numbers = random(1, pow(2, 32) - 1, i, 10);
            a.emplace_back(numbers[numbers.size() - 1]);
        }*/

        // For testing.
        a.emplace_back(166);
        a.emplace_back(94);

        for (int i = 1; i <= n; i++) {
            D.emplace_back(evaluatePolynomial(a, i));
        }
        cout << "";

    } catch (const exception& e) {
        output_buffer->text("Error: Invalid input values");
    }
}

// Callback function for Generate button
/*void generate_callback(Fl_Widget* widget, void* data) {
    try {
        const uint64_t seed = stoull(seed_input->value());
        const uint64_t min_val = stoull(min_input->value());
        const uint64_t max_val = stoull(max_input->value());
        const int count = stoi(count_input->value());

        if (min_val >= max_val) {
            output_buffer->text("Error: Min must be less than Max");
            return;
        }

        if (count <= 0 || count > 10000) {
            output_buffer->text("Error: Count must be between 1 and 10000");
            return;
        }

        vector<uint64_t> numbers = random(min_val, max_val, seed, count);

        string result = "Generated " + to_string(count) + " random numbers:\n\n";

        // Show first 50 numbers
        int display_count = min(count, 50);
        for (int i = 0; i < display_count; i++) {
            result += "Number " + to_string(i + 1) + ": " + to_string(numbers[i]) + "\n";
        }

        if (count > 50) {
            result += "\n... (showing first 50 of " + to_string(count) + " numbers)\n";
        }

        result += "\nLast number: " + to_string(numbers[count - 1]);

        output_buffer->text(result.c_str());

    } catch (const exception& e) {
        output_buffer->text("Error: Invalid input values");
    }
}*/

int main() {
    auto *window = new Fl_Window(600, 550, "Secret Sharing");

    // Title
    auto *title = new Fl_Box(20, 10, 560, 30, "LCG Random Number Generator");
    title->labelsize(16);
    title->labelfont(FL_BOLD);

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

    // Generate button
    auto *generate_btn = new Fl_Button(225, 170, 150, 40, "Generate Numbers");
    generate_btn->callback(divide_secret);


    /*// Input fields
    auto *seed_label = new Fl_Box(20, 50, 100, 30, "Seed:");
    seed_label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    seed_input = new Fl_Input(130, 50, 450, 30);
    seed_input->value("1");

    auto *min_label = new Fl_Box(20, 90, 100, 30, "Min Value:");
    min_label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    min_input = new Fl_Input(130, 90, 450, 30);
    min_input->value("0");

    auto *max_label = new Fl_Box(20, 130, 100, 30, "Max Value:");
    max_label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    max_input = new Fl_Input(130, 130, 450, 30);
    max_input->value("100");

    auto *count_label = new Fl_Box(20, 170, 100, 30, "Count:");
    count_label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    count_input = new Fl_Input(130, 170, 450, 30);
    count_input->value("10");

    // Generate button
    auto *generate_btn = new Fl_Button(225, 220, 150, 40, "Generate Numbers");
    generate_btn->callback(generate_callback);

    // Output display
    auto *output_label = new Fl_Box(20, 270, 100, 30, "Output:");
    output_label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
*/

    output_buffer = new Fl_Text_Buffer();
    output_display = new Fl_Text_Display(20, 300, 560, 230);
    output_display->buffer(output_buffer);

    window->end();
    window->show();

    return Fl::run();
}