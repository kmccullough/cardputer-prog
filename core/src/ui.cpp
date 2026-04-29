#include <cstdint>
#include "core/ui.h"
#include "core/colors.h"

void UI::setup() {

}

const uint demoDelay = 3000;
const uint demoRow = 20;

uint demoIndex = 0;
uint32_t demoStart = 0;
uint demoStuff = 0;

#define BEGIN_DEMO demoStart = now(); demoStuff = 0; subTimer.reset()
#define NEXT_DEMO ++demoIndex

void UI::loop() {
    uint demoNext = 0;
    if (demoIndex == demoNext++) {
        BEGIN_DEMO;
        log("Text Demo (%d)", demoStart);
        fillScreen(Colors::Background);
        setRotation(1);
        setTextColor(Colors::Foreground, Colors::Background);
        setTextSize(2);
        setCursor(0, 0);
        println("Cardputer-prog");
        setCursor(0, 15);
        println("Graphics Demo");
        setTextSize(1);
        setCursor(0, 30);
        println("Text, shapes,");
        setCursor(0, 45);
        println("lines, colors");
        delay(demoDelay);
        NEXT_DEMO;
    } else if (demoIndex == demoNext++ && !delayed()) {
        BEGIN_DEMO;
        log("Line Demo (%d)", demoStart = now());
        fillScreen(Colors::Background);
        setCursor(0, 0);
        println("Line Demo");
        for (uint x = 0; x < width; ++x) {
            Color color { 
                (uint8_t)(x > 255 ? 255 : x),
                255,
                (uint8_t)(x > 255 ? 0 : 255 - x)
            };
            drawLine(0, demoRow, x, height, color);
        }
        delay(demoDelay);
        NEXT_DEMO;
    } else if (demoIndex == demoNext++ && !delayed()) {
        BEGIN_DEMO;
        log("Shapes Demo (%d)", demoStart = now());
        fillScreen(Colors::Background);
        setCursor(0, 0);
        println("Shapes Demo");
        drawRect(10, demoRow, 60, 40, Colors::Red);
        fillRect(80, demoRow, 60, 40, Colors::Blue);
        drawCircle(50, 90, 20, Colors::Green);
        fillCircle(130, 90, 20, Colors::Yellow);
        drawTriangle(170, demoRow, 210, 50, 150, 50, Colors::Cyan);
        delay(demoDelay);
        NEXT_DEMO;
    } else if (demoIndex == demoNext++ && !delayed()) {
        BEGIN_DEMO;
        log("Gradient / Pixel Demo (%d)", demoStart = now());
        fillScreen(Colors::Background);
        setCursor(0, 0);
        println("Gradient / Pixel Demo");
        for (uint x = 0; x < width; ++x) {
            for (uint y = demoRow; y < height; ++y) {
                Color color { 
                    (uint8_t)x, 
                    (uint8_t)y,
                    (uint8_t)((x + y) % 255)
                };
                drawPixel(x, y, color);
            }
        }
        delay(demoDelay);
        NEXT_DEMO;
    } else if (demoIndex == demoNext++ && !delayed()) {
        bool cleared = false;
        if (subTimer.isReset()) {
            BEGIN_DEMO;
            log("Animation Demo (%d)", demoStart = now());
            fillScreen(Colors::Background);
            setCursor(0, 0);
            println("Animation Demo");
            cleared = true;
        }
        if (subTimer.isComplete()) {
            if (!cleared) {
                fillScreen(Colors::Background);
            }
            setCursor(0, 0);
            println("Animation Demo");
            log("Animation Step (%d)", now());
            fillScreen(Colors::Background);
            int x = (demoStuff * 2) % 240;
            int y = 67;
            fillCircle(x, y, 10, Colors::Orange);
            drawString("Moving ball", 10, 10);
            subTimer.start(30);
            ++demoStuff;
        }
        if (demoStuff >= 120) {
            delay(demoDelay);
            NEXT_DEMO;
        }
    } else if (demoIndex == demoNext++ && !delayed()) {
        BEGIN_DEMO;
        log("Done (%d)", demoStart = now());
        fillScreen(Colors::Background);
        setCursor(0, 0);
        println("Done!");
        NEXT_DEMO;
    }

}

uint32_t UI::now() {
    return clock.now();
}

UI& UI::delay(uint32_t delay) {
    if (delay) {
        timer.start(delay);
        log("Delay: %d (%d) (->%d)", delay, now(), timer.endTime());
    }
    return *this;
}

bool UI::delayed() {
    if (timer.isReset()) {
        log("No Delay");
        return false;
    }
    if (timer.isComplete()) {
        log("Delay (->%d) (%d)", timer.endTime(), now());
        timer.reset();
        return false;
    }
    return true;
}

UI& UI::execute(std::function<void(UI&)> fn) {
    fn(*this);
    return *this;
}
