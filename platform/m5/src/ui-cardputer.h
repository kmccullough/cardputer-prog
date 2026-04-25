#pragma once
#include "core/color.h"
#include "core/ui.h"

class UICardputer : public UI {
    bool init() override;

    UI* clear() override;
    UI* drawRect(int, int, int, int, Color) override;
    UI* fillRect(int, int, int, int, Color) override;
    UI* print(const std::string& s) override;
    UI* println(const std::string& s) override;
    UI* setCursor(int, int) override;
    UI* setTextColor(uint8_t, uint8_t, uint8_t, uint8_t = 255) override;
    UI* setTextSize(int) override;
};
