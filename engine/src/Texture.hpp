#pragma once

#include "core_api.hpp"

#include <iostream>
#include <cstdio>
#include <cstdint>
#include <string>
#include <SDL.h>

#include "Context.hpp"

namespace engine
{

class Texture
{
public:
	CORE_API Texture();
    CORE_API Texture(Context&, const Texture&);
	CORE_API ~Texture();

	CORE_API void set(SDL_Surface*);
	CORE_API void copy(Texture*);
	CORE_API void create(Context&);
	CORE_API void create(Context&, SDL_Surface*);
    CORE_API void update(SDL_Surface*);
    CORE_API void update();
    CORE_API Texture subTexture(Context&, int, int, int, int);
	CORE_API uint32_t getW();
	CORE_API uint32_t getH();
	CORE_API SDL_Texture* use();
    CORE_API SDL_Surface* getSurface();
    CORE_API void destroy();
    CORE_API void setName(const std::string&);
    CORE_API std::string getName();

    bool ready;

private:
    uint32_t w;
    uint32_t h;
    std::string name;
    SDL_Texture* tex;
    SDL_Surface* surf;
};

}
