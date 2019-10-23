#include "Scoreboard.hpp"
#include <iostream>

Scoreboard::~Scoreboard()
{

}

void Scoreboard::init(Context& ctx)
{
    l0.loadAnimation("assets/numbers.json");
    l1.loadAnimation("assets/numbers.json");
    r0.loadAnimation("assets/numbers.json");
    r1.loadAnimation("assets/numbers.json");

    l0.x = -64;
    l1.x = -128;

    r0.x = 64;
    r1.x = 128;

    addChild(&l0);
    addChild(&l1);
    addChild(&r0);
    addChild(&r1);

    //l0.setCurrentFrame(1);
    //l1.setCurrentFrame(1);
    //r0.setCurrentFrame(1);
    //r1.setCurrentFrame(1);


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
    //drawChildren(ctx, 0.0f, Point(x, y));
}
