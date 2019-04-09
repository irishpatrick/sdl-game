#pragma once

#include <engine.hpp>

class MapTest : public engine::State
{
public:
    MapTest();
    ~MapTest();

    void init(engine::Context&);
    void update(float);
    void render(engine::Context&);

private:
    engine::TileMap map;
};
