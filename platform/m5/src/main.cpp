#include <Arduino.h>
#include <M5Unified.h>
#include <M5Cardputer.h>
#include "app-context-m5.h"

void setup() {
    app.init();
    app.ui.setup();
}

void loop() {
    M5.update();

    auto ks = M5Cardputer.Keyboard.keysState();
    
    for (auto c : ks.word) {
        Serial.print((char)c);
        M5.Display.print((char)c);
    }

    app.ui.loop();
}
