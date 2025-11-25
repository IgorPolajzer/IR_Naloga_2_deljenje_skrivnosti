//
// Created by igork on 01/11/2025.
//

#include "lcg.h"
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

std::vector<cpp_int> lcg(const cpp_int &m, const cpp_int &a, const cpp_int &b, const cpp_int &ro, int size) {
    std::vector<cpp_int> r(size);
    r[0] = ro;

    for (size_t i = 1; i < size; i++) {
        r[i] = (a * r[i - 1] + b) % m;
    }

    return r;
}

std::vector<cpp_int> random(const cpp_int &x, const cpp_int &y, const cpp_int &ro, int size) {
    const cpp_int m = boost::multiprecision::pow(cpp_int(2), 32);
    const cpp_int a = 69069;
    const cpp_int b = 0;

    std::vector<cpp_int> numbers = lcg(m, a, b, ro, size);

    for (auto & number : numbers) {
        number = x + (number % (y - x + 1));
    }

    return numbers;
}