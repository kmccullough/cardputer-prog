#include <iostream>
#include "ui-desktop.h"
#include "app-context-desktop.h"

void setup() {
    if (!app.init()) {
        return app.exit(1);
    }
    app.ui.setup();
}

void loop() {
    SDL_Event e;

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

    app.ui.loop();
}

int main() {
    app.ui.beforeRender();
    setup();
    app.ui.afterRender();
    while (app.running) {
        app.ui.beforeRender();
        loop();
        app.ui.afterRender();
    }
    app.cleanup();
    return 0;
}
