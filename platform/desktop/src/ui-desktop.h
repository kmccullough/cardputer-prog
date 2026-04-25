#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "core/color.h"
#include "core/ui.h"

class UIDesktop : public UI {
public:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;

    bool init() override;
    void cleanup();
    UIDesktop* clear() override;
    UIDesktop* drawRect(int, int, int, int, Color) override;
    UIDesktop* fillRect(int, int, int, int, Color) override;
    UIDesktop* setTextSize(int) override;
    UIDesktop* setTextColor(uint8_t, uint8_t, uint8_t, uint8_t = 255) override;
    UIDesktop* setCursor(int, int) override;
    UIDesktop* print(const std::string&) override;
    UIDesktop* println(const std::string&) override;
};
