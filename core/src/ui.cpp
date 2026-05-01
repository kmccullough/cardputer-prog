#include <algorithm>
#include <cstdint>
#include "core/colors.h"
#include "core/grid.h"
#include "core/ui.h"

void UI::setup() {

}

const uint32_t demoDelay = 3000;
const uint32_t demoRow = 8;

uint8_t demoIndex = 0;
uint32_t demoStart = 0;
uint8_t demoStuff = 0;

#define BEGIN_DEMO demoStart = now(); demoStuff = 0; subTimer.reset()
#define NEXT_DEMO ++demoIndex

void UI::loop() {
    uint8_t demoNext = 0;
    if (demoIndex == demoNext++) {
        BEGIN_DEMO;
        log("Text Demo (%d)", demoStart);
        fillScreen(Colors::Background);
        setRotation(1);
        setTextColor(Colors::Foreground, Colors::Background);
        setCursor(0, 0);
        println("╔════════════════════════════╗");
        println("║                            ║");
        println("║                            ║");
        println("║   ┌───┬────────────┬───┐   ║");
        println("║   │ ╔═╧════════════╧═╗ │   ║");
        println("║   ├─╢ Cardputer-prog ╟─┤   ║");
        println("║   │ ║ Graphics Demo  ║ │   ║");
        println("║   ╞═╬═══════╦════════╬═╡   ║");
        println("║   │ ║ TEXT  ║ SHAPES ║ │   ║");
        println("║   │ ╠═══════╬════════╣ │   ║");
        println("║   ├─╢ LINES ║ COLORS ╟─┤   ║");
        println("║   │ ╚═╤═════╩══════╤═╝ │   ║");
        println("║   └───┴────────────┴───┘   ║");
        println("║                            ║");
        println("║    by Kerry McCullough     ║");
        println("║                            ║");
        println("╚════════════════════════════╝");
        delay(demoDelay);
        NEXT_DEMO;
    } else if (demoIndex == demoNext++ && !delayed()) {
        BEGIN_DEMO;
        log("Line Demo (%d)", demoStart = now());
        fillScreen(Colors::Background);
        setCursor(0, 0);
        println("Line Demo");
        for (uint32_t x = 0; x < width; ++x) {
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
        uint32_t demoHeight = height - demoRow;
        uint8_t demosH = 3;
        uint8_t demosV = 2;
        float demoPad = .2;
        float demoH = padCell(width, demosH, demoPad);
        float demoV = padCell(demoHeight, demosV, demoPad);
        float demoHalfH = demoH / 2;
        float demoHalfV = demoV / 2;
        float demoMin = std::min(demoH, demoV);
        float demoPadH = demoPad * demoH;
        float demoPadV = demoPad * demoV;
        uint32_t demoRow1 = demoRow + demoPadV;
        uint32_t demoRow2 = demoRow + demoPadV * 2 + demoV;
        uint32_t demoCol1 = demoPadH;
        uint32_t demoCol2 = demoPadH * 2 + demoH;
        uint32_t demoCol3 = demoPadH * 3 + demoH * 2;
        drawRect(demoCol1, demoRow1, demoH, demoV, Colors::Red);
        fillRect(demoCol1, demoRow2, demoH, demoV, Colors::Blue);
        drawCircle(
            demoCol2 + demoHalfH,
            demoRow1 + demoHalfV,
            demoMin / 2,
            Colors::Green
        );
        fillCircle(
            demoCol2 + demoHalfH,
            demoRow2 + demoHalfV,
            demoMin / 2,
            Colors::Yellow
        );
        drawTriangle(
            demoCol3 + demoHalfH,
            demoRow1,
            demoCol3,
            demoRow1 + demoV,
            demoCol3 + demoH,
            demoRow1 + demoV,
            Colors::Cyan
        );
        fillTriangle(
            demoCol3 + demoHalfH,
            demoRow2,
            demoCol3,
            demoRow2 + demoV,
            demoCol3 + demoH,
            demoRow2 + demoV,
            Colors::Magenta
        );
        delay(demoDelay);
        NEXT_DEMO;
    } else if (demoIndex == demoNext++ && !delayed()) {
        BEGIN_DEMO;
        log("Gradient / Pixel Demo (%d)", demoStart = now());
        fillScreen(Colors::Background);
        setCursor(0, 0);
        println("Gradient / Pixel Demo");
        for (uint32_t x = 0; x < width; ++x) {
            for (uint32_t y = demoRow; y < height; ++y) {
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
            fillScreen(Colors::Background);
            int x = (demoStuff * 2) % 240;
            int y = 67;
            fillCircle(x, y, 10, Colors::Orange);
            drawString("Moving ball", 0, 0);
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
    }
    return *this;
}

bool UI::delayed() {
    if (timer.isReset()) {
        return false;
    }
    if (timer.isComplete()) {
        timer.reset();
        return false;
    }
    return true;
}

UI& UI::execute(std::function<void(UI&)> fn) {
    fn(*this);
    return *this;
}
