#include <Arduino.h>
#include <M5Unified.h>
#include "app-context-cardputer.h"
#include "ui-cardputer.h"

AppContextCardputer app;

bool AppContextCardputer::init() {
    auto cfg = M5.config();
    M5.begin(cfg);
    Serial.begin(115200);
    return true;
}
