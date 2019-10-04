#include "Light.hpp"
#include <SDL.h>
#include <cstdint>
#include "Texture.hpp"

namespace engine
{
    Light::Light() :
        obeyCamera(true),
        intensity(1.0),
        temperature(0.5)
    {
        color.setRGB(1.0, 1.0, 1.0);
    }

    Light::~Light()
    {

    }

    void Light::setObeyCamera(bool val)
    {
        obeyCamera = val;
    }

    void Light::setIntensity(double val)
    {
        intensity = val;
    }

    void Light::draw(Context& ctx, float ex)
    {
        ctx.pushCfg();
        ctx.getCfg()->useCamera = obeyCamera;
        ctx.getCfg()->mode = SDL_BLENDMODE_ADD;
        //ctx.getCfg()->mode = SDL_BLENDMODE_MOD;

        uint8_t i = (uint8_t)(intensity * 255);
        double r, g, b;
        r = intensity * color.getRGB().r.f;
        g = intensity * color.getRGB().g.f;
        b = intensity * color.getRGB().g.f;

        SDL_SetTextureColorMod(texture->use(), r * 255, g * 255, b * 255);
        //SDL_SetTextureColorMod(texture->use(), r, g, b);
        Sprite::draw(ctx, ex);
        ctx.popCfg();
    }
}