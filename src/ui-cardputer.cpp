#include <cstdint>
#include <M5Unified.h>
#include "ui-cardputer.h"

bool UICardputer::init() {
    return true;
}

UICardputer* UICardputer::clear() {
    M5.Display.clear();
    return this;
}

UICardputer* UICardputer::drawRect(int x, int y, int w, int h, Color c) {
    M5.Display.drawRect(x, y, w, h, M5.Display.color565(c.r, c.g, c.b));
    return this;
}

UICardputer* UICardputer::fillRect(int x, int y, int w, int h, Color c) {
    M5.Display.fillRect(x, y, w, h, M5.Display.color565(c.r, c.g, c.b));
    return this;
}

UICardputer* UICardputer::setTextSize(int size) {
    M5.Display.setTextSize(size);
    return this;
}

UICardputer* UICardputer::setTextColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    this->textColor = { r, g, b, 255 };
    M5.Display.setTextColor(M5.Display.color565(r, g, b));
    return this;
}

UICardputer* UICardputer::setCursor(int x, int y) {
    M5.Display.setCursor(x, y);
    this->cursorPosition = { x, y };
    return this;
}

UICardputer* UICardputer::print(const std::string& text) {
    M5.Display.print(text.c_str());
    return this;
}

UICardputer* UICardputer::println(const std::string& text) {
    M5.Display.println(text.c_str());
    return this;
}
