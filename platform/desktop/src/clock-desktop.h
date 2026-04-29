#pragma once
#include <cstdint>
#include <SDL.h>
#include "core/clock.h"

struct ClockDesktop : Clock {
    uint32_t now() const override {
        return SDL_GetTicks();
    }
};
