#pragma once
#include <cstdint>
#include "core/clock.h"

class Timer {
protected:
    const Clock& clock;
    bool _reset = true;
    bool _active = false;
    uint32_t _startTime = 0;
    uint32_t _endTime = 0;
    uint32_t _duration = 0;
    uint32_t _runtime = 0;

public:
    Timer(const Clock& clock) 
        : clock(clock) {}

    uint32_t start(uint32_t duration = 0) {
        _reset = false;
        _active = true;
        _startTime = clock.now();
        _duration = duration;
        return _endTime = _duration == 0 ? 0 : _startTime + _duration;
    }
    uint32_t end() {
        _active = false;
        _endTime = clock.now();
        return _runtime = _endTime - _startTime;
    }
    void reset() {
        _reset = true;
        _active = false;
        _startTime = _endTime = _duration = _runtime = 0;
    }

    bool isReset() const {
        return _reset;
    }    
    bool isActive() {
        if (_active && _duration != 0 
            && _endTime <= clock.now()
        ) {
            end();
        }
        return _active;
    }
    bool isComplete() {
        return !isActive();
    }

    uint startTime() const {
        return _startTime;
    }
    uint duration() const {
        return _duration;
    }
    uint endTime() const {
        return _endTime;
    }
    uint runtime() const {
        return _runtime;
    }
};
