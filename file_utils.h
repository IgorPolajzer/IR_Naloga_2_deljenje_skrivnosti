//
// Created by igork on 25/11/2025.
//

#ifndef NALOGA_2_DELJENJE_SKRIVNOSTI_FILE_UTILS_H
#define NALOGA_2_DELJENJE_SKRIVNOSTI_FILE_UTILS_H
#include <boost/multiprecision/cpp_int.hpp>

class Fl_File_Chooser;
using boost::multiprecision::cpp_int;

void open_file_dialog(Fl_File_Chooser &chooser);

cpp_int read_file_as_int(const std::string &file_name);

#endif //NALOGA_2_DELJENJE_SKRIVNOSTI_FILE_UTILS_H