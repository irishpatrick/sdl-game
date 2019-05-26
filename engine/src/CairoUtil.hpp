#pragma once

#include <cairo.h>
#include <cstdint>

namespace engine
{
    class CairoUtil
    {
    public:
        static void drawVector(cairo_t*, uint32_t, uint32_t, uint32_t, double);
    };
}