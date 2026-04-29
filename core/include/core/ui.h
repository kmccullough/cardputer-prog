#pragma once
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include "core/clock.h"
#include "core/color.h"
#include "core/position.h"
#include "core/timer.h"

class UI {
protected:
    const Clock& clock;
    Timer timer;
    Timer subTimer;
    Color textColor { 255, 255, 255 };
    Color backgroundTextColor = { 0, 0, 0 };
    Position cursorPosition { 0, 0 };

public:
    UI(const Clock& clock)
        : clock(clock),
          timer(clock),
          subTimer(clock) {}

    const uint width = 240;
    const uint height = 135;

    void setup();
    void loop();
    uint32_t now();
    UI& delay(uint);
    bool delayed();

    UI& execute(std::function<void(UI&)>);

    virtual bool init() = 0;
    virtual UI& log(const char* format, ...) = 0;

    virtual UI& drawCircle(int, int, int, Color) = 0;
    virtual UI& drawLine(int, int, int, int, Color) = 0;
    virtual UI& drawPixel(int, int, Color) = 0;
    virtual UI& drawRect(int, int, int, int, Color) = 0;
    virtual UI& drawString(const std::string&, int, int) = 0;
    virtual UI& drawTriangle(int, int, int, int, int, int, Color) = 0;
    virtual UI& fillCircle(int, int, int, Color) = 0;
    virtual UI& fillRect(int, int, int, int, Color) = 0;
    virtual UI& fillScreen(Color) = 0;
    virtual UI& fillTriangle(int, int, int, int, int, int, Color) = 0;
    virtual UI& print(const std::string&) = 0;
    virtual UI& println(const std::string&) = 0;
    virtual UI& setCursor(int, int) = 0;
    virtual UI& setRotation(int) = 0;
    virtual UI& setTextColor(Color) = 0;
    virtual UI& setTextColor(Color, Color) = 0;
    virtual UI& setTextSize(int) = 0;
};
