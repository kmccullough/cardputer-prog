#pragma once

#include "clock.h"
#include "ui.h"

struct AppContext {
    // IInput* input = nullptr;
    // VM* vm = nullptr;

    // int screenWidth = 800;
    // int screenHeight = 600;

    virtual bool init() = 0;
};
