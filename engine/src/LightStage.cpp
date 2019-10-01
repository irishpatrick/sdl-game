#include "LightStage.hpp"
#include "Assets.hpp"
#include "Texture.hpp"

namespace engine
{
    LightStage::LightStage() :
        Sprite()
    {

    }

    LightStage::~LightStage()
    {
        if (texture != nullptr)
        {
            delete texture;
        }
    }

    void LightStage::init(Context& ctx)
    {
        w = ctx.getWidth();
        h = ctx.getHeight();
        clear.create(ctx, ctx.getWidth(), ctx.getHeight());
        cairo_t* cr = clear.getCairo();
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_rectangle(cr, 0, 0, ctx.getWidth(), ctx.getHeight());
        cairo_fill(cr);
        clear.update();

        texture = new Texture();
        texture->createTarget(ctx, ctx.getWidth(), ctx.getHeight());
    }

    void LightStage::addLight(Light* light)
    {
        lights.push_back(light);
    }

    void LightStage::draw(Context& ctx, float ex)
    {
        ctx.pushCfg();
        ctx.getCfg()->useCamera = false;
        ctx.getCfg()->renderTarget = texture->use();

        //SDL_SetRenderTarget(ctx.getRenderer(), texture->use());
        //SDL_SetRenderDrawColor(ctx.getRenderer(), 0x00, 0x00, 0x00, 0xFF);
        //SDL_RenderClear(ctx.getRenderer());

        clear.draw(ctx);

        for (auto& e : lights)
        {
            e->draw(ctx, ex);
        }

        ctx.popCfg();

        ctx.pushCfg();
        ctx.getCfg()->useCamera = false;
        ctx.getCfg()->mode = SDL_BLENDMODE_MOD;

        Sprite::draw(ctx, ex);

        ctx.popCfg();
    }
}