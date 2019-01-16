#pragma once

#include <engine.hpp>

class Title : public engine::State
{
public:
    Title() : State()
    {
        
    }

    ~Title()
    {

    }

    void init(engine::Context&) override;
    void update(float) override;
    void render(engine::Context&) override;

private:
    engine::Sprite background;
	engine::Transition transition;
};
