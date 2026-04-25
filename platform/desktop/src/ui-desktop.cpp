#include <cstdint>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "app-context-desktop.h"
#include "ui-desktop.h"

std::string getResourcePath(const std::string& relativePath);

bool UIDesktop::init() {
    // Initialize SDL for graphics
    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to initialize graphics\n";
        return false;
    }
    // Initialize font system
    if (TTF_Init()) {
        std::cerr << "Failed to initialize fonts\n";
        return false;
    }
    // Enable antialiasing
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    // Create SDL window
    this->window = SDL_CreateWindow(
        "Cardputer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        0
    );
    if (!this->window) {
        std::cerr << "Failed to initialize window\n";
        return false;
    }
    // Create SDL renderer
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if (!this->renderer) {
        std::cerr << "Failed to initialize window\n";
        return false;
    }
    // Load font
    std::string fontPath = getResourcePath("assets/fonts/JetBrainsMono-Regular.ttf");
    this->font = TTF_OpenFont(fontPath.c_str(), 16);
    if (!this->font) {
        std::cerr << "Font failed to load: " << TTF_GetError() << "\n";
        return false;
    }
    return true;
}

void UIDesktop::cleanup() {
    if (this->font) {
        TTF_CloseFont(this->font);
    }
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
    }
    if (this->window) {
        SDL_DestroyWindow(this->window);
    }
    TTF_Quit();
    SDL_Quit();
}

UI* UIDesktop::clear() {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255); // black
    SDL_RenderClear(this->renderer);
    return this;
}

UI* UIDesktop::drawRect(int x, int y, int w, int h, Color c) {
    SDL_Rect rect = { x, y, w, h };
    SDL_SetRenderDrawColor(this->renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawRect(this->renderer, &rect);
    return this;
}

UI* UIDesktop::fillRect(int x, int y, int w, int h, Color c) {
    SDL_Rect rect = { x, y, w, h };
    SDL_SetRenderDrawColor(this->renderer, c.r, c.g, c.b, c.a);
    SDL_RenderFillRect(this->renderer, &rect);
    return this;
}

UI* UIDesktop::setTextSize(int size) {
    // TODO write font handling to create new fonts at sizes as needed and cache
    return this;
}

UI* UIDesktop::setTextColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    this->textColor = { r, g, b, a };
    return this;
}

UI* UIDesktop::setCursor(int x, int y) {
    this->cursorPosition = { x, y };
    return this;
}

UI* UIDesktop::print(const std::string& text) {
    SDL_Color color = { this->textColor.r, this->textColor.g, this->textColor.b, this->textColor.a };
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    if (!surface) {
        std::cerr << "RenderText failed: " << TTF_GetError() << "\n";
        return this;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_Rect textRect = {
        this->cursorPosition.x, this->cursorPosition.y, 
        surface->w, surface->h 
    };
    SDL_RenderCopy(this->renderer, texture, NULL, &textRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(this->renderer);
    return this;
}

UI* UIDesktop::println(const std::string& text) {
    this->print(text);
    // TODO move cursor to next line
    return this;
}

std::string getResourcePath(const std::string& relativePath) {
    char* baseDir = SDL_GetBasePath();
    std::string fullPath = "";
    if (baseDir) {
        fullPath = std::string(baseDir) + relativePath;
        SDL_free(baseDir);
    } else {
        fullPath = "./" + relativePath;
    }
    return fullPath;
}
