#pragma once
#include "core/app-context.h"
#include "app-context-m5.h"
#include "ui-m5.h"

struct AppContextM5 : AppContext {
    UIM5 ui;

    bool init();
};

extern AppContextM5 app;
