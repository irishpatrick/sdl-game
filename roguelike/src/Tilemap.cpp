#include "Tilemap.hpp"
#include <iostream>
#include <fstream>

Tilemap::Tilemap()
{
    atlas = nullptr;
}

Tilemap::~Tilemap()
{

}

void Tilemap::setTextureAtlas(Texture* tex)
{
    atlas = tex;
}

void Tilemap::extractTextures(const std::string& fn)
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


}
