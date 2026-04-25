#pragma once
#include <cstdint>

struct Color {
    uint8_t r, g, b, a = 255;
    constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) 
        : r(r), g(g), b(b), a(a) { }
};
