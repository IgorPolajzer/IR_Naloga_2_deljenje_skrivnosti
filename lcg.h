//
// Created by igork on 01/11/2025.
//

#ifndef NALOGA_2_DELJENJE_SKRIVNOSTI_LCG_H
#define NALOGA_2_DELJENJE_SKRIVNOSTI_LCG_H

#ifndef LCG_H
#define LCG_H

#include <vector>
#include <cstdint>

std::vector<int> lcg(int m, int a, int b, int ro, size_t size);
std::vector<int> random(int x, int y, int ro, int size = 1000);

#endif // LCG_H

#endif //NALOGA_2_DELJENJE_SKRIVNOSTI_LCG_H