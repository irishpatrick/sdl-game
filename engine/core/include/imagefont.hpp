#pragma once

#include "core_api.hpp"

#include <map>
#include <string>
#include <cstdint>
#include <SDL2/SDL.h>

using namespace std;

namespace engine {

class Texture;

class ImageFont
{
public:
	CORE_API ImageFont();
	CORE_API ~ImageFont();

	CORE_API void setScale(float);
	CORE_API void setTexture(Texture*);
	CORE_API void buildMap();
	CORE_API void setColor(uint8_t, uint8_t, uint8_t);
	CORE_API void renderChar(const string&, float, float, SDL_Renderer*);
	CORE_API void renderString(const string&, float, float, SDL_Renderer*);

private:
    Texture* tex;
    uint32_t w;
    uint32_t h;
	uint8_t maskR, maskG, maskB;
    bool isMaskSet;
    float scale;
    SDL_Rect* crects;
    const std::string charMap = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
};

}
