#include "Light.hpp"
#include <SDL.h>

namespace engine
{
    Light::Light()
    {

    }

    Light::~Light()
    {

    }

    void Light::draw(Context& ctx, float ex)
    {
        ctx.pushCfg();
        /*ctx.getCfg()->mode = SDL_ComposeCustomBlendMode(
            SDL_BLENDFACTOR_SRC_COLOR,
            SDL_BLENDFACTOR_DST_COLOR,
            SDL_BLENDOPERATION_ADD,

        );*/
        ctx.getCfg()->mode = SDL_BLENDMODE_ADD;
        Sprite::draw(ctx, ex);
        ctx.popCfg();
    }
}