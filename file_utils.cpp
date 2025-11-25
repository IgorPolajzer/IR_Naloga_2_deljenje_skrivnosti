//
// Created by igork on 25/11/2025.
//

#include "file_utils.h"

#include <fstream>
#include <iterator>
#include <string>
#include <FL/Fl_File_Chooser.H>

using boost::multiprecision::cpp_int;

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

    // Read bytes
    std::vector bytes(
        (std::istreambuf_iterator(file)),
         std::istreambuf_iterator<char>()
    );

    file.close();

    // Convert bytes to cpp_int
    cpp_int result = 0;
    for (auto byte : bytes) {
        result <<= 8;
        result |= byte;
    }

    return result;
}
