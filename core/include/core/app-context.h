#pragma once

#include "ui.h"

struct AppContext {
    UI* ui = nullptr;

    // IInput* input = nullptr;
    // VM* vm = nullptr;

    // int screenWidth = 800;
    // int screenHeight = 600;

    virtual bool init() = 0;
};
