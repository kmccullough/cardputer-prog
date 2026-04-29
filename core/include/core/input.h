#pragma once
#include <string>

struct Input {
public:
    virtual bool poll(std::string& out) = 0;
};
