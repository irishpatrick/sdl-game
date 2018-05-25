#pragma once

#include <cstdint>

namespace engine {

class AsyncTimer {
public:
    AsyncTimer();
    ~AsyncTimer();

    void start(uint32_t);
    bool poll();
};

}
