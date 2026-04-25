#include "app-context-cardputer.h"
#include "ui-cardputer.h"

AppContextCardputer app;

bool AppContextCardputer::init() {
    this->ui = new UICardputer;
    return true;
}
