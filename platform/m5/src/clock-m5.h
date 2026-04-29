#pragma once
#include <Arduino.h>
#include <cstdint>
#include "core/clock.h"

struct ClockM5 : Clock {
    uint32_t now() const override{
        return millis();
    };
};
