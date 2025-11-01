//
// Created by igork on 01/11/2025.
//

#include "lcg.h"

std::vector<uint64_t> lcg(uint64_t m, uint64_t a, uint64_t b, uint64_t ro, size_t size) {
    std::vector<uint64_t> r(size);
    r[0] = ro;

    for (size_t i = 1; i < size; i++) {
        r[i] = (a * r[i - 1] + b) % m;
    }

    return r;
}

std::vector<uint64_t> random(uint64_t x, uint64_t y, uint64_t ro, size_t size) {
    uint64_t m = (1ULL << 32);
    uint64_t a = 69069;
    uint64_t b = 0;

    std::vector<uint64_t> numbers = lcg(m, a, b, ro, size);

    for (size_t i = 0; i < numbers.size(); i++) {
        numbers[i] = x + (numbers[i] % (y - x + 1));
    }

    return numbers;
}