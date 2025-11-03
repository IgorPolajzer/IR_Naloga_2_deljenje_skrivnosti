//
// Created by igork on 01/11/2025.
//

#include "lcg.h"
#include <cmath>

std::vector<int> lcg(int m, int a, int b, int ro, int size) {
    std::vector<int> r(size);
    r[0] = ro;

    for (size_t i = 1; i < size; i++) {
        r[i] = (a * r[i - 1] + b) % m;
    }

    return r;
}

std::vector<int> random(int x, int y, int ro, int size) {
    int m = pow(2, 32);
    int a = 69069;
    int b = 0;

    std::vector<int> numbers = lcg(m, a, b, ro, size);

    for (size_t i = 0; i < numbers.size(); i++) {
        numbers[i] = x + (numbers[i] % (y - x + 1));
    }

    return numbers;
}