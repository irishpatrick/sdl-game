#include "Npc.hpp"
#include "Textbox.hpp"
#include <iostream>

Npc::Npc() : 
    Player()
{

}

Npc::~Npc()
{
    
}

void Npc::init()
{

}

void Npc::update()
{
    Player::update();
}

void Npc::draw(float ex)
{
    Context& ctx = MyEngine::getContext();
    GridSprite::draw(ctx, ex);
}

void Npc::interact(GridSprite* prompt)
{
    Textbox::reset();
    Textbox::fillDialogue("hello, player!");
    Textbox::play();
}
