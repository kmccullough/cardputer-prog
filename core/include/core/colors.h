#include "color.h"

namespace Colors {
    static constexpr Color Black   = { 0, 0, 0 };
    static constexpr Color White   = { 255, 255, 255 };
    static constexpr Color Gray    = { 128, 128, 128 };
    static constexpr Color DarkGray= { 64, 64, 64 };
    static constexpr Color LightGray= { 192, 192, 192 };
    static constexpr Color Red     = { 255, 0, 0 };
    static constexpr Color Green   = { 0, 255, 0 };
    static constexpr Color Blue    = { 0, 0, 255 };
    static constexpr Color Yellow  = { 255, 255, 0 };
    static constexpr Color Orange  = { 255, 165, 0 };
    static constexpr Color Purple  = { 128, 0, 128 };
    static constexpr Color Cyan    = { 0, 255, 255 };
    static constexpr Color Magenta = { 255, 0, 255 };

    static constexpr Color Transparent = { 255, 255, 255, 255 };
    static constexpr Color Background = Black;
    static constexpr Color Foreground = White;
    static constexpr Color Accent     = Cyan;

    static constexpr Color Success = Green;
    static constexpr Color Warning = Yellow;
    static constexpr Color Error   = Red;

    // Cardputer-friendly dim UI tones
    static constexpr Color Panel   = { 20, 20, 20 };
    static constexpr Color Border  = { 80, 80, 80 };
    static constexpr Color Muted   = { 160, 160, 160 };
}
