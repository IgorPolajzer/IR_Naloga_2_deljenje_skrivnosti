//
// Created by igork on 01/11/2025.
//

#ifndef NALOGA_2_DELJENJE_SKRIVNOSTI_LCG_H
#define NALOGA_2_DELJENJE_SKRIVNOSTI_LCG_H

#ifndef LCG_H
#define LCG_H

#include <vector>
#include <cstdint>

std::vector<uint64_t> lcg(uint64_t m, uint64_t a, uint64_t b, uint64_t ro, size_t size);
std::vector<uint64_t> random(uint64_t x, uint64_t y, uint64_t ro, size_t size = 1000);

#endif // LCG_H

#endif //NALOGA_2_DELJENJE_SKRIVNOSTI_LCG_H