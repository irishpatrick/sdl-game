#pragma once

#include "core.hpp"
#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <SDL.h>

namespace engine
{
    typedef struct _Tile
    {
        SDL_Rect tex;
        bool solid;
    } Tile;
    class TileMap2 : public Sprite
    {
    public:
        TileMap2();
        ~TileMap2();

        void open(const std::string&);

    private:
        uint32_t w;
        uint32_t t;
        Texture* tex;
        std::vector<Tile> tilemap;
    };
}

