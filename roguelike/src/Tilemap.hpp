#pragma once

#include <engine.hpp>
#include <vector>

using namespace engine;

class Tilemap
{
public:
    Tilemap();
    ~Tilemap();

    void setTextureAtlas(Texture*);
    void extractTextures(const std::string&);

private:
    Texture* atlas;
    std::vector<Sprite*> tiles;
    std::vector<Texture*> textures;
};