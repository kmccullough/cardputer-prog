#pragma once
#include <string>

struct Input {
public:
    virtual bool poll(std::string& out) = 0;
    virtual ~Input() = default;
};
