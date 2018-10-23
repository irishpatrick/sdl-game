#pragma once

#include <engine.hpp>

class DialogueBox : public engine::Sprite
{
public:
    DialogueBox() : Sprite()
    {

    }

    ~DialogueBox()
    {

    }

    engine::ScrollingText text;
};