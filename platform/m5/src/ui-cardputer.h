#pragma once
#include "core/color.h"
#include "core/ui.h"

struct UICardputer : UI {
public:
    bool init() override;
    UICardputer* clear() override;
    UICardputer* drawRect(int, int, int, int, Color) override;
    UICardputer* fillRect(int, int, int, int, Color) override;
    UICardputer* setTextSize(int) override;
    UICardputer* setTextColor(uint8_t, uint8_t, uint8_t, uint8_t = 255) override;
    UICardputer* setCursor(int, int) override;
    UICardputer* print(const std::string& s) override;
    UICardputer* println(const std::string& s) override;
};
