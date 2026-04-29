#include <cstdint>
#include <M5Unified.h>
#include "ui-m5.h"

bool UIM5::init() {
    return true;
}

uint16_t UIM5::getColor(Color c) {
    return M5.Display.color565(c.r, c.g, c.b);
}

UI& UIM5::log(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int size = vsnprintf(nullptr, 0, format, args);
    va_end(args);
    if (size > 0) {
        std::vector<char> buffer(size + 1);
        va_start(args, format);
        vsnprintf(buffer.data(), buffer.size(), format, args);
        va_end(args);
        Serial.print(buffer.data());
    }
    return *this;
}

UI& UIM5::drawCircle(int x, int y, int r, Color c) {
    M5.Display.drawCircle(x, y, r, getColor(c));
    return *this;
}

UI& UIM5::drawLine(int x1, int y1, int x2, int y2, Color c) {
    M5.Display.drawLine(x1, y1, x2, y2, getColor(c));
    return *this;
}

UI& UIM5::drawPixel(int x, int y, Color c) {
    M5.Display.drawPixel(x, y, getColor(c));
    return *this;
}

UI& UIM5::drawRect(int x, int y, int w, int h, Color c) {
    M5.Display.drawRect(x, y, w, h, getColor(c));
    return *this;
}

UI& UIM5::drawString(const std::string& text, int x, int y) {
    M5.Display.drawString(text.c_str(), x, y);
    return *this;
}

UI& UIM5::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Color c) {
    M5.Display.drawTriangle(x1, y1, x2, y2, x3, y3, getColor(c));
    return *this;
}

UI& UIM5::fillCircle(int x, int y, int r, Color c) {
    M5.Display.fillCircle(x, y, r, getColor(c));
    return *this;
}

UI& UIM5::fillRect(int x, int y, int w, int h, Color c) {
    M5.Display.fillRect(x, y, w, h, getColor(c));
    return *this;
}

UI& UIM5::fillScreen(Color c) {
    M5.Display.fillScreen(getColor(c));
    return *this;
}

UI& UIM5::fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Color c) {
    M5.Display.fillTriangle(x1, y1, x2, y2, x3, y3, getColor(c));
    return *this;
}

UI& UIM5::print(const std::string& text) {
    M5.Display.print(text.c_str());
    return *this;
}

UI& UIM5::println(const std::string& text) {
    M5.Display.println(text.c_str());
    return *this;
}

UI& UIM5::setCursor(int x, int y) {
    M5.Display.setCursor(x, y);
    cursorPosition = { x, y };
    return *this;
}

UI& UIM5::setRotation(int rotation) {
    M5.Display.setRotation(rotation);
    return *this;
}

UI& UIM5::setTextColor(Color fg) {
    textColor = fg;
    M5.Display.setTextColor(getColor(fg));
    return *this;
}

UI& UIM5::setTextColor(Color fg, Color bg) {
    textColor = fg;
    backgroundTextColor = bg;
    M5.Display.setTextColor(getColor(fg), getColor(bg));
    return *this;
}

UI& UIM5::setTextSize(int size) {
    M5.Display.setTextSize(size);
    return *this;
}
