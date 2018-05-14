#pragma once

#include <cstdint>

namespace engine {

class Mouse {
public:
    static inline void set(uint32_t a, uint32_t b, bool l, bool m, bool r) {
        x = a;
        y = b;
        left = l;
        middle = m;
        right = r;
    }

    static inline uint32_t getX() {
        return x;
    }

    static inline uint32_t getY() {
        return y;
    }

    static inline bool isLeftDown() {
        return left;
    }

    static inline bool isMiddleDown() {
        return middle;
    }

    static inline bool isRightDown() {
        return right;
    }

    static uint32_t x;
    static uint32_t y;
    static bool left;
    static bool middle;
    static bool right;
};

}
