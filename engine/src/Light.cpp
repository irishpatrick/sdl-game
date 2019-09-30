#include "Light.hpp"
#include <SDL.h>
#include <cstdint>
#include "Texture.hpp"

namespace engine
{
    Light::Light() :
        intensity(1.0),
        temperature(0.5)
    {
        color.setRGB(1.0, 1.0, 1.0);
    }

    Light::~Light()
    {

    }

    void Light::setIntensity(double val)
    {
        intensity = val;
    }

    void Light::draw(Context& ctx, float ex)
    {
        ctx.pushCfg();
        /*ctx.getCfg()->mode = SDL_ComposeCustomBlendMode(
            SDL_BLENDFACTOR_SRC_COLOR,
            SDL_BLENDFACTOR_DST_COLOR,
            SDL_BLENDOPERATION_ADD,

        );*/
        //ctx.getCfg()->useCamera = false;
        ctx.getCfg()->mode = SDL_BLENDMODE_MOD;
        uint8_t i = (uint8_t)(intensity * 255);
        double r, g, b;
        r = intensity * color.getRGB().r.f;
        g = intensity * color.getRGB().g.f;
        b = intensity * color.getRGB().g.f;

        SDL_SetTextureColorMod(texture->use(), r * 255, g * 255, b * 255);
        Sprite::draw(ctx, ex);
        ctx.popCfg();
    }
}