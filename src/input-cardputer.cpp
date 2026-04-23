#include <M5Unified.h>
#include <M5Cardputer.h>
#include "input.h"

struct CardputerInput : public Input {
public:
    bool poll(std::string& out) override {
        M5.update();

        auto ks = M5Cardputer.Keyboard.keysState();

        if (ks.word.empty()) {
            out = std::string(ks.word.begin(), ks.word.end());
            return true;
        }

        return false;
    }
};
