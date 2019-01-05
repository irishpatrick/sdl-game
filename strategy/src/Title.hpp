#pragma once

#include <engine.hpp>

class Title : public engine::State

{
public:
    Title();
    ~Title();

    void init(engine::Context&);

private:
    engine::Sprite background;
};
