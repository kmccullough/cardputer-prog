#pragma once
#include "core/app-context.h"
#include "clock-m5.h"
#include "ui-m5.h"

struct AppContextM5 : AppContext {
    ClockM5 clock;
    UIM5 ui;

    AppContextM5()
        : clock(),
          ui(clock) {}

    bool init();
};

extern AppContextM5 app;
