//
// Created by igork on 25/11/2025.
//

#include "file_utils.h"

#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <FL/Fl_File_Chooser.H>

using boost::multiprecision::cpp_int;
using boost::multiprecision::cpp_rational;

void open_file_dialog(Fl_File_Chooser &chooser) {
    chooser.show();

    // Wait until the user closes the dialog
    while (chooser.shown()) {
        Fl::wait();
    }

    if (chooser.value() != nullptr) {
        printf("Selected file: %s\n", chooser.value());
    }
}

cpp_int read_file_as_int(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("Cannot open file");

    // Read all bytes
    std::vector<unsigned char> bytes((std::istreambuf_iterator<char>(file)),
                                      std::istreambuf_iterator<char>());

    cpp_int number;
    import_bits(number, bytes.begin(), bytes.end(), true);
    return number;
}

void write_int_as_file(cpp_int number) {
    std::vector<unsigned char> bytes;
    export_bits(number, std::back_inserter(bytes), 8);

    std::ofstream file("output.pdf", std::ios::binary);
    if (!file) throw std::runtime_error("Cannot open file for writing");

    file.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
}

std::vector<std::pair<cpp_int, cpp_int>> read_parts_to_vector() {
    std::vector<std::pair<cpp_int, cpp_int>> parts;

    for (const auto &entry : std::filesystem::directory_iterator("divided_files")) {
        if (entry.is_regular_file()) {
            std::ifstream file(entry.path());

            std::string line;
            while (std::getline(file, line)) {
                // Format: number;big_number
                auto semicolon_pos = line.find(';');
                if (semicolon_pos != std::string::npos) {
                    cpp_int first(line.substr(0, semicolon_pos));
                    cpp_int second(line.substr(semicolon_pos + 1));
                    parts.emplace_back(first, second);
                }
            }
        }
    }

    return parts;
}

