#pragma once
#include "color.h"
#include "ui.h"

struct UICardputer : UI {
public:
    bool init();
    UICardputer* clear();
    UICardputer* drawRect(int, int, int, int, Color);
    UICardputer* fillRect(int, int, int, int, Color);
    UICardputer* setTextSize(int);
    UICardputer* setTextColor(uint8_t, uint8_t, uint8_t, uint8_t = 255);
    UICardputer* setCursor(int, int);
    UICardputer* print(const std::string& s);
    UICardputer* println(const std::string& s);
};
