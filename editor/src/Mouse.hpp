#pragma once

#include <cstdint>
#include "Point.hpp"

class Mouse
{
public:
    static void poll();
    static Point getPos();
    static int getLeft();
    static int getRight();
    static void setScale(float);

private:
    static int x;
    static int y;
    static int left;
    static int right;
    static uint32_t state;
    static float scale;
};