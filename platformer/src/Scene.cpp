#include "Scene.hpp"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

void Scene::load(const std::string& fn)
{
    json o = engine::Util::loadJson(fn);
}

void Scene::update(float delta)
{
    platforms.update(delta);
    sprites.update(delta);
}

void Scene::draw(engine::Context& ctx, engine::Camera& camera)
{
    platforms.draw(ctx, camera);
    sprites.draw(ctx, camera);
}
