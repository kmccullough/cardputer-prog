#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include "core/color.h"
#include "core/ui.h"

class UIM5 : public UI {
protected:
    uint16_t getColor(Color);

public:
    UIM5(const Clock& clock)
        : UI(clock) {}

    bool init() override;

    UI& log(const char* format, ...) override;

    UI& drawCircle(int, int, int, Color) override;
    UI& drawPixel(int, int, Color) override;
    UI& drawLine(int, int, int, int, Color) override;
    UI& drawRect(int, int, int, int, Color) override;
    UI& drawString(const std::string&, int32_t, int32_t) override;
    UI& drawTriangle(int, int, int, int, int, int, Color) override;
    UI& fillCircle(int, int, int, Color) override;
    UI& fillRect(int, int, int, int, Color) override;
    UI& fillScreen(Color) override;
    UI& fillTriangle(int, int, int, int, int, int, Color) override;
    UI& print(const std::string&) override;
    UI& println(const std::string& = "") override;
    UI& printup(const std::string& = "") override;
    UI& scroll(int_fast16_t, int_fast16_t) override;
    UI& setBaseColor(Color c) override;
    UI& setCursor(int, int) override;
    UI& setRotation(int) override;
    UI& setScrollRect(int32_t, int32_t, int32_t, int32_t) override;
    UI& setTextColor(Color) override;
    UI& setTextColor(Color, Color) override;
    UI& setTextSize(int) override;
};
