#include "core/ui.h"

void UI::run() {
    this->clear()
        ->drawRect(10, 20, 30, 40, Color{ 0, 128, 255, 255 })
        ->setTextSize(2)
        ->setCursor(0, 0)
        ->println("Cardputer ready")
    ;
}
