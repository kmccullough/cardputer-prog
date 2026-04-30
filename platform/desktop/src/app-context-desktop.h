#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "core/app-context.h"
#include "clock-desktop.h"
#include "ui-desktop.h"

struct AppContextDesktop : AppContext {
    bool running = true;
    int exitCode = 0;

    ClockDesktop clock;
    UIDesktop ui;

    AppContextDesktop()
        : clock(),
          ui(clock) {}

    bool init();

    void exit(int exitCode = 0);
    void cleanup();
};

extern AppContextDesktop app;
