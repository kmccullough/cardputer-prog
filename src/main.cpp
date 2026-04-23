#include <Arduino.h>
#include <M5Unified.h>
#include <M5Cardputer.h>
#include "app-context-cardputer.h"

void initialize();

void setup() {
    initialize();
    app.ui
        ->clear()
        ->drawRect(10, 20, 30, 40, Color{ 0, 128, 255, 255 })
        ->setTextSize(2)
        ->setCursor(0, 0)
        ->println("Cardputer ready")
    ;
}

void loop() {
    M5.update();

    auto ks = M5Cardputer.Keyboard.keysState();
    
    for (auto c : ks.word) {
        Serial.print((char)c);
        M5.Display.print((char)c);
    }
}

void initialize() {
    auto cfg = M5.config();
    M5.begin(cfg);
    Serial.begin(115200);
    app.init();
}
