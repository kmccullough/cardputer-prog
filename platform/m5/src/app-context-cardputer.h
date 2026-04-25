#pragma once

#include "core/app-context.h"
#include "app-context-cardputer.h"
#include "ui-cardputer.h"

struct AppContextCardputer : AppContext {
    UICardputer* ui = nullptr;

    bool init();
};

extern AppContextCardputer app;
