#include <iostream>
#include "app-context-desktop.h"
#include "ui-desktop.h"

AppContextDesktop app;

bool AppContextDesktop::init() {
    if (!this->ui.init()) {
        std::cerr << "Failed to initialize UI\n";
        return false;
    }
    return true;
}

void AppContextDesktop::exit(int exitCode) {
    this->exitCode = exitCode;
    this->running = false;
}

void AppContextDesktop::cleanup() {
    this->ui.cleanup();
}
