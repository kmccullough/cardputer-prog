#include <Arduino.h>
#include <M5Unified.h>
#include "app-context-m5.h"
#include "ui-m5.h"

AppContextM5 app;

bool AppContextM5::init() {
    auto cfg = M5.config();
    M5.begin(cfg);
    Serial.begin(115200);
    return true;
}
