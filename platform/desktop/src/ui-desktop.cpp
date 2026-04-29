#include <cstdint>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <thread>
#include "core/colors.h"
#include "app-context-desktop.h"
#include "ui-desktop.h"

std::string getResourcePath(const std::string& relativePath);
void fillFlatBottomTriangle(SDL_Renderer* r, int x1, int y1, int x2, int y2, int x3, int y3);
void fillFlatTopTriangle(SDL_Renderer* r, int x1, int y1, int x2, int y2, int x3, int y3);

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
    window = SDL_CreateWindow(
        "Cardputer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        0
    );
    if (!window) {
        std::cerr << "Failed to initialize window\n";
        return false;
    }
    // Create SDL renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to initialize window\n";
        return false;
    }
    // Create buffer
    renderCache = SDL_CreateTexture(renderer, 
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        width, height
    );
    // Load font
    std::string fontPath = getResourcePath("assets/fonts/JetBrainsMono-Regular.ttf");
    font = TTF_OpenFont(fontPath.c_str(), 16);
    if (!font) {
        std::cerr << "Font failed to load: " << TTF_GetError() << "\n";
        return false;
    }
    return true;
}

void UIDesktop::cleanup() {
    if (font) {
        TTF_CloseFont(font);
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    TTF_Quit();
    SDL_Quit();
}

void UIDesktop::beforeRender() {
    SDL_SetRenderTarget(renderer, renderCache);
}

void UIDesktop::afterRender() {
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, renderCache, NULL, NULL);
    SDL_RenderPresent(renderer);
}

SDL_Color UIDesktop::getColor(Color c) {
    return SDL_Color { c.r, c.g, c.b, c.a };
}

UI& UIDesktop::log(const char* format, ...) {
    va_list args;
    
    va_start(args, format);
    int size = vsnprintf(nullptr, 0, format, args);
    va_end(args);

    if (size <= 0) return *this;

    std::vector<char> buffer(size + 1);

    va_start(args, format);
    vsnprintf(buffer.data(), buffer.size(), format, args);
    va_end(args);

    SDL_Log("%s", buffer.data());

    return *this;
}

UI& UIDesktop::drawCircle(int cx, int cy, int r, Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    int x = r - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (r << 1);
    while (x >= y) {
        SDL_RenderDrawPoint(renderer, cx + x, cy + y);
        SDL_RenderDrawPoint(renderer, cx + y, cy + x);
        SDL_RenderDrawPoint(renderer, cx - y, cy + x);
        SDL_RenderDrawPoint(renderer, cx - x, cy + y);
        SDL_RenderDrawPoint(renderer, cx - x, cy - y);
        SDL_RenderDrawPoint(renderer, cx - y, cy - x);
        SDL_RenderDrawPoint(renderer, cx + y, cy - x);
        SDL_RenderDrawPoint(renderer, cx + x, cy - y);
        if (err <= 0) {
            ++y;
            err += dy;
            dy += 2;
        }
        if (err > 0) {
            --x;
            dx += 2;
            err += dx - (r << 1);
        }
    }
    return *this;
}

UI& UIDesktop::drawLine(int x1, int y1, int x2, int y2, Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    return *this;
}

UI& UIDesktop::drawPixel(int x, int y, Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawPoint(renderer, x, y);
    return *this;
}

UI& UIDesktop::drawRect(int x, int y, int w, int h, Color c) {
    SDL_Rect rect = { x, y, w, h };
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawRect(renderer, &rect);
    return *this;
}

UI& UIDesktop::drawString(const std::string& text, int x, int y) {
    SDL_Color color = getColor(textColor);
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    if (!surface) {
        std::cerr << "RenderText failed: " << TTF_GetError() << "\n";
        return *this;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    return *this;
}

UI& UIDesktop::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
    SDL_RenderDrawLine(renderer, x3, y3, x1, y1);
    return *this;
}

UI& UIDesktop::fillCircle(int cx, int cy, int r, Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    for (int w = -r; w <= r; ++w) {
        for (int h = -r; h <= r; ++h) {
            if (w * w + h * h <= r * r) {
                SDL_RenderDrawPoint(renderer, cx + w, cy + h);
            }
        }
    }
    return *this;
}

UI& UIDesktop::fillRect(int x, int y, int w, int h, Color c) {
    SDL_Rect rect = { x, y, w, h };
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderFillRect(renderer, &rect);
    return *this;
}

UI& UIDesktop::fillScreen(Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderClear(renderer);
    return *this;
}

UI& UIDesktop::fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    if (y1 > y2) { std::swap(y1, y2); std::swap(x1, x2); }
    if (y2 > y3) { std::swap(y2, y3); std::swap(x2, x3); }
    if (y1 > y2) { std::swap(y1, y2); std::swap(x1, x2); }
    if (y2 == y3) {
        fillFlatBottomTriangle(renderer, x1, y1, x2, y2, x3, y3);
    } else if (y1 == y2) {
        fillFlatTopTriangle(renderer, x1, y1, x2, y2, x3, y3);
    } else {
        int x4 = (int)(x1 + ((float)(y2 - y1) / (y3 - y1)) * (x3 - x1));
        int y4 = y2;
        fillFlatBottomTriangle(renderer, x1, y1, x2, y2, x4, y4);
        fillFlatTopTriangle(renderer, x2, y2, x4, y4, x3, y3);
    }
    return *this;
}

UI& UIDesktop::print(const std::string& text) {
    drawString(text, cursorPosition.x, cursorPosition.y);
    return *this;
}

UI& UIDesktop::println(const std::string& text) {
    print(text);
    // TODO move cursor to next line
    return *this;
}

UI& UIDesktop::setCursor(int x, int y) {
    cursorPosition = { x, y };
    return *this;
}

UI& UIDesktop::setRotation(int rotation) {
    // TODO
    return *this;
}

UI& UIDesktop::setTextColor(Color fg) {
    textColor = fg;
    backgroundTextColor = Colors::Transparent;
    return *this;
}

UI& UIDesktop::setTextColor(Color fg, Color bg) {
    textColor = fg;
    backgroundTextColor = bg;
    return *this;
}

UI& UIDesktop::setTextSize(int size) {
    // TODO write font handling to create new fonts at sizes as needed and cache
    return *this;
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

void fillFlatBottomTriangle(SDL_Renderer* r, int x1, int y1, int x2, int y2, int x3, int y3) {
    float invslope1 = (float)(x2 - x1) / (y2 - y1);
    float invslope2 = (float)(x3 - x1) / (y3 - y1);
    float curx1 = x1;
    float curx2 = x1;
    for (int scanlineY = y1; scanlineY <= y2; scanlineY++) {
        SDL_RenderDrawLine(r, (int)curx1, scanlineY, (int)curx2, scanlineY);
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

void fillFlatTopTriangle(SDL_Renderer* r, int x1, int y1, int x2, int y2, int x3, int y3) {
    float invslope1 = (float)(x3 - x1) / (y3 - y1);
    float invslope2 = (float)(x3 - x2) / (y3 - y2);
    float curx1 = x3;
    float curx2 = x3;
    for (int scanlineY = y3; scanlineY > y1; --scanlineY) {
        SDL_RenderDrawLine(r, (int)curx1, scanlineY, (int)curx2, scanlineY);
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}
