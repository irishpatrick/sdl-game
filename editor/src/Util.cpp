#include "Util.hpp"

Pointf Util::toScreenScpace(Point* p, engine::Context* ctx)
{
    Pointf out;
    out.x = ((float)p->x / (float)ctx->getWidth()) - 0.5f;
    out.y = ((float)p->y / (float)ctx->getHeight()) - 0.5f;
    return out;
}

Point Util::toPixelSpace(Pointf* p, engine::Context* ctx)
{
    Point out;
    out.x = (int)((p->x + 0.5f) * ctx->getWidth());
    out.y = (int)((p->y + 0.5f) * ctx->getHeight());
    printf("out: %d, %d\n", out.x, out.y);
    return out;
}