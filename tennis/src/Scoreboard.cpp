#include "Scoreboard.hpp"

Scoreboard::~Scoreboard()
{

}

void Scoreboard::init(Context& ctx)
{
    l0.init(ctx, "assets/numbers.json");
    l1.init(ctx, "assets/numbers.json");
    r0.init(ctx, "assets/numbers.json");
    r1.init(ctx, "assets/numbers.json");

    l0.x = -100;
    l1.x = -100 + l0.w;

    r0.x = 100;
    r1.x = 100 + r0.w;

    addChild(&l0);
    addChild(&l1);
    addChild(&r0);
    addChild(&r1);

    x = ctx.getWidth() / 2;
    y = 20;
}
