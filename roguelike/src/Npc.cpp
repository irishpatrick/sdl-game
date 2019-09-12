#include "Npc.hpp"

Npc::Npc() : 
    GridSprite()
{

}

Npc::~Npc()
{
    
}

void Npc::init()
{
    text.init();
    text.x = 32;
    text.y = 32;
}

void Npc::update()
{

}

void Npc::draw(float ex)
{
    Context& ctx = MyEngine::getContext();
    GridSprite::draw(ctx, ex);
    text.draw(ex);
}

void Npc::interact(GridSprite* prompt)
{
    text.reset();
    text.fillDialogue("hello, player!");
    text.play();
}