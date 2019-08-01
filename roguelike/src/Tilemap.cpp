#include "Tilemap.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Tilemap::Tilemap()
{
    atlas = nullptr;
}

Tilemap::~Tilemap()
{
    for (auto& e : textures)
    {
        delete e;
    }

    for (auto& e : tiles)
    {
        delete e.second;
    }
}

void Tilemap::setTextureAtlas(Texture* tex)
{
    atlas = tex;
}

void Tilemap::extractTextures(Context& ctx, const std::string& fn)
{
    if (atlas == nullptr)
    {
        return;
    }

    std::ifstream fp(fn);
    std::vector<std::string> names;
    if (fp.is_open())
    {
        std::string str;
        while (std::getline(fp, str))
        {
            names.push_back(str);
        }
    }

    int rows = 32;
    int cols = 32;
    int size = 32;
    int margin = 1;

    int i;
    int j;
    int n = 0;

    for (i = 0; i < rows; ++i)
    {
        int y = (i * size) + (i * (margin + (margin / 2))) + (margin / 2) + 1;
        for (j = 0; j < cols; ++j)
        {
            int x = (j * size) + (j * (margin + (margin / 2))) + (margin / 2) + 1;
            textures.push_back(new Texture(atlas->subTexture(ctx, x, y, size, size)));
        }
    }

    for (auto& e : names)
    {
        Sprite* s = new Sprite();
        s->name = e;
        s->setTexture(textures[n++]);
        tiles[e] = s;
    }
}

void Tilemap::extractLayout(Context& ctx, const std::string& fn)
{
    std::ifstream fp(fn);
    if (!fp.is_open())
    {
        std::cout << "error" << std::endl;
        return;
    }

    std::string str;
    while (std::getline(fp, str))
    {
        std::vector<std::string> tokens;
        std::istringstream stream(str);
        std::string part;
        while (std::getline(stream, part, '\t'))
        {

        }
    }
}

Sprite* Tilemap::getSprite(int index)
{
    return nullptr;
}
