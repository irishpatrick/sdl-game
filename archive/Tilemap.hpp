/*#pragma once

#include <engine.hpp>
#include <vector>
#include <map>

using namespace engine;

class Tilemap
{
public:
    Tilemap();
    ~Tilemap();

    void setTextureAtlas(Texture*);
    void extractTextures(Context&, const std::string&);
    void extractLayout(Context&, const std::string&);
    Sprite* getSprite(int);
    Sprite* getTile(const std::string&);

private:
    Texture* atlas;
    std::map<std::string, Sprite*> tiles;
    std::vector<std::string> layout;
    std::vector<Texture*> textures;
};*/
