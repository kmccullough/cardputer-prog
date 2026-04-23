#pragma once
#include <cstdint>
#include <string>
#include "color.h"
#include "position.h"

struct UI {
protected:
    Color textColor { 255, 255, 255, 255 };
    Position cursorPosition { 0, 0 };
public:
    virtual bool init() = 0;
    virtual UI* clear() = 0;
    virtual UI* drawRect(int, int, int, int, Color) = 0;
    virtual UI* fillRect(int, int, int, int, Color) = 0;
    virtual UI* setTextSize(int) = 0;
    virtual UI* setTextColor(uint8_t, uint8_t, uint8_t, uint8_t = 255) = 0;
    virtual UI* setCursor(int, int) = 0;
    virtual UI* print(const std::string&) = 0;
    virtual UI* println(const std::string&) = 0;
};
