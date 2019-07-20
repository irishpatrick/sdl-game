#include "Opponent.hpp"

void Opponent::init(Context& ctx)
{
    setTexture(Assets::getTexture("opponent.png"));
    x = ctx.getWidth() / 2 - w / 2;
    y = 0.5 * h;
    hitbox.xywh(0, h / 2 - 10, w, h / 2);
}