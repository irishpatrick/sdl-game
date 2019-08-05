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
    l1.x = -164;

    r0.x = 100;
    r1.x = 164;

    addChild(&l0);
    addChild(&l1);
    addChild(&r0);
    addChild(&r1);

    l0.setCurrentFrame(1);
    l1.setCurrentFrame(1);
    r0.setCurrentFrame(1);
    r1.setCurrentFrame(1);


    x = ctx.getWidth() / 2;
    y = 20;
}

void Scoreboard::update()
{
    l0.update();
    l1.update();
    r0.update();
    r1.update();
}

void Scoreboard::draw(Context& ctx)
{
    l0.draw(ctx);
    l1.draw(ctx);
    r0.draw(ctx);
    r1.draw(ctx);
}
