#pragma once

#include "core_api.hpp"

#include <cstdio>
#include <cstdint>
#include <string>
#include <SDL2/SDL.h>

namespace engine {

class Texture
{
public:
	CORE_API Texture();
	CORE_API Texture(SDL_Renderer*);
	CORE_API ~Texture();

	CORE_API void set(SDL_Surface*);
	CORE_API void copy(Texture*);
	CORE_API void create(SDL_Renderer*);
	CORE_API uint32_t getW();
	CORE_API uint32_t getH();
	CORE_API SDL_Texture* use();
	CORE_API void destroy();

	CORE_API inline std::string getName() {
        return name_;
    }

    bool ready;

private:
    uint32_t w;
    uint32_t h;
    std::string name_;
    SDL_Texture* tex;
    SDL_Surface* surf;
    SDL_Renderer* renderer;
};

}
