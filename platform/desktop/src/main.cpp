#include <iostream>
#include "ui-desktop.h"
#include "app-context-desktop.h"

void initialize();

void setup() {
    initialize();
    app.ui
        ->clear()
        ->drawRect(10, 20, 30, 40, Color{ 0, 128, 255, 255 })
        ->setTextSize(2)
        ->setCursor(0, 0)
        ->println("Cardputer ready")
    ;
}

void loop() {
    // M5.update();

    // auto ks = M5Cardputer.Keyboard.keysState();
    
    // for (auto c : ks.word) {
    //     Serial.print((char)c);
    //     M5.Display.print((char)c);
    // }
}

void initialize() {
    if (!app.init()) {
        return app.exit(1);
    }
}

int main() {
    SDL_Event e;

    setup();

    while (app.running) {

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                app.running = false;
            }

            if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
                SDL_Keycode key = e.key.keysym.sym;

                switch (key) {
                    case SDLK_a:
                        std::cout << "A pressed\n";
                        break;

                    case SDLK_BACKSPACE:
                        std::cout << "backspace\n";
                        break;

                    case SDLK_RETURN:
                        std::cout << "enter\n";
                        break;
                }
            }
        }

        loop();
    }

    app.cleanup();
    return 0;
}
