#pragma once

#include <engine.hpp>
#include <string>

class Scene
{
public:
    Scene() {}
    ~Scene() {}

    void load(const std::string&);
    void update(float);
    void draw(engine::Context&, engine::Camera&);


private:
    engine::Group platforms;
    engine::Group sprites;
};