#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "color.h"
#include "ui.h"

class UIDesktop : public UI {
public:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;

    bool init();
    void cleanup();
    UIDesktop* clear();
    UIDesktop* drawRect(int, int, int, int, Color);
    UIDesktop* fillRect(int, int, int, int, Color);
    UIDesktop* setTextSize(int);
    UIDesktop* setTextColor(uint8_t, uint8_t, uint8_t, uint8_t = 255);
    UIDesktop* setCursor(int, int);
    UIDesktop* print(const std::string&);
    UIDesktop* println(const std::string&);
};
