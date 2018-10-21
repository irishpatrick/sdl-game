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
    void update(float, const unsigned char*) override;
    void render(engine::Context&) override;

private:
    engine::Sprite background;
    
};
