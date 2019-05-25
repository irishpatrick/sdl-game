#pragma once

#include <engine.hpp>
#include "Point.hpp"

class Util
{
public:
    static Pointf toScreenScpace(Point*, engine::Context*);
    static Point toPixelSpace(Pointf*, engine::Context*);
};