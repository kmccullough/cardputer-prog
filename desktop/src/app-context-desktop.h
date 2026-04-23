#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "ui-desktop.h"
#include "app-context.h"

struct AppContextDesktop : AppContext {
    bool running = true;
    int exitCode = 0;

    UIDesktop* ui = nullptr;

    bool init();
    void exit(int exitCode = 0);
    void cleanup();
};

extern AppContextDesktop app;
