#pragma once
#include <cstdint>

struct Clock {
    virtual uint32_t now() const = 0;
};
