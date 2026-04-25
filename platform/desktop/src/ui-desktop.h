#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "core/color.h"
#include "core/ui.h"

class UIDesktop : public UI {
protected:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;

public:
    bool init() override;

    UI* clear() override;
    UI* drawRect(int, int, int, int, Color) override;
    UI* fillRect(int, int, int, int, Color) override;
    UI* print(const std::string&) override;
    UI* println(const std::string&) override;
    UI* setCursor(int, int) override;
    UI* setTextColor(uint8_t, uint8_t, uint8_t, uint8_t = 255) override;
    UI* setTextSize(int) override;

    void cleanup();
};
