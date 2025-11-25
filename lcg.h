//
// Created by igork on 01/11/2025.
//

#ifndef NALOGA_2_DELJENJE_SKRIVNOSTI_LCG_H
#define NALOGA_2_DELJENJE_SKRIVNOSTI_LCG_H

#ifndef LCG_H
#define LCG_H

#include <vector>
#include <cstdint>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

std::vector<int> lcg(cpp_int m, cpp_int a, cpp_int b, cpp_int ro, size_t size);
std::vector<int> random(cpp_int x, cpp_int y, cpp_int ro, int size = 1000);

#endif // LCG_H

#endif //NALOGA_2_DELJENJE_SKRIVNOSTI_LCG_H