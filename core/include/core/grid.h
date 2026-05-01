#pragma once
#include <cstdint>

float padCell(uint32_t size, uint32_t cells, float padRatio = 0) {
    return size / (cells + padRatio * (cells + 1));
}
