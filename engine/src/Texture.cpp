#include "Texture.hpp"
#include "MyEngine.hpp"
#include <iostream>
#include <SDL.h>
#include <cstdint>

namespace engine
{

	Texture::Texture()
	{
		w = 0;
		h = 0;
        tex = nullptr;
        surf = nullptr;
		ready = false;
		name = "";
	}

    Texture::Texture(const Texture& t)
    {
        w = t.w;
        h = t.h;
        ready = t.ready;
        surf = t.surf;
        tex = t.tex;
    }

    Texture::Texture(Context& ctx, const Texture& t)
    {
        w = t.w;
        h = t.h;
        ready = t.ready;
        SDL_UnlockSurface(t.surf);
        surf = SDL_CreateRGBSurface(
            t.surf->flags,
            w,
            h,
            t.surf->format->BitsPerPixel,
            t.surf->format->Rmask,
            t.surf->format->Gmask,
            t.surf->format->Bmask,
            t.surf->format->Amask
        );
        SDL_BlitSurface(t.surf, nullptr, surf, nullptr);
        tex = nullptr;
        create(ctx);
    }

	Texture::~Texture()
	{
        destroy();
	}

	uint32_t Texture::getW()
	{
		return w;
	}

	uint32_t Texture::getH()
	{
		return h;
	}

	void Texture::set(SDL_Surface* s)
	{
		surf = s;
		w = surf->w;
		h = surf->h;
		ready = true;
	}

	void Texture::copy(Texture* t)
	{
        std::cout << "BAD" << std::endl;
		w = t->getW();
		h = t->getH();
		tex = t->use();
		ready = true;
	}

	void Texture::create(Context& ctx)
	{
        int relock = 0;

        if (surf->locked)
        {
            relock = 1;
            SDL_UnlockSurface(surf);
        }
		tex = SDL_CreateTextureFromSurface(ctx.getRenderer(), surf);
        if (relock)
        {
            SDL_LockSurface(surf);
        }

		if (tex == nullptr) {
			std::cout << "(" << name << ") error: cannot create texture: " << SDL_GetError() << std::endl;
		}
	}

	void Texture::create(Context& ctx, SDL_Surface* s)
	{
		surf = s;
        int relock = 0;

        if (s->locked)
        {
            relock = 1;
            SDL_UnlockSurface(s);
        }
		tex = SDL_CreateTextureFromSurface(ctx.getRenderer(), s);
        if (relock)
        {
            SDL_LockSurface(s);
        }

        if (tex == nullptr)
		{
			std::cout << "texture error: (" << name << ") " << SDL_GetError() << std::endl;
			return;
		}
		w = s->w;
		h = s->h;
		ready = true;
	}

    void Texture::create(Context& ctx, int w, int h)
    {
        uint32_t rmask, gmask, bmask, amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif
        
        surf = SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);
    
        SDL_FillRect(surf, nullptr, 0x000000);

        create(ctx);
    }

    void Texture::createTarget(Context& ctx, int w, int h)
    {
        //SDL_RendererInfo = SDL_GetRendererInfo(ctx.getRenderer());
        
        surf = nullptr;
        tex = SDL_CreateTexture(
            ctx.getRenderer(),
            SDL_PIXELFORMAT_RGBA8888, 
            SDL_TEXTUREACCESS_TARGET,
            w,
            h
        );
        if (tex == nullptr)
        {
            std::cout << "Texture::createTarget error: " << SDL_GetError() << std::endl;
        }

        ready = true;
    }

    void Texture::update(SDL_Surface* s)
    {
        if (s == nullptr)
        {
            //std::cout << "error: surface was null" << std::endl;
            return;
        }
        if (tex == nullptr)
        {
            //std::cout << "error: texture was null" << std::endl;
            return;
        }
        int relock = 0;
        if (s->locked)
        {
            relock = 1;
            SDL_UnlockSurface(s);
        }
        SDL_UpdateTexture(tex, NULL, s->pixels, s->pitch);
        if (relock)
        {
            SDL_LockSurface(s);
        }
    }

    void Texture::update()
    {
        Texture::update(surf);
    }

    Texture Texture::subTexture(Context& ctx, int x, int y, int w, int h)
    {
        // crop sdl surface
        SDL_Surface* subsurf = SDL_CreateRGBSurface(
            surf->flags, 
            w, h, 
            surf->format->BitsPerPixel, 
            surf->format->Rmask, 
            surf->format->Gmask, 
            surf->format->Bmask, 
            surf->format->Amask
        );
        SDL_Rect r = { x, y, w, h };
        SDL_BlitSurface(surf, &r, subsurf, nullptr);
        Texture out;
        out.create(ctx, subsurf);

        return out;
    }

    Texture* Texture::subTextureP(Context& ctx, int x, int y, int w, int h)
    {
        Texture* out = new Texture();
        SDL_Surface* subs = SDL_CreateRGBSurface(
            surf->flags,
            w, h,
            surf->format->BitsPerPixel,
            surf->format->Rmask,
            surf->format->Gmask,
            surf->format->Bmask,
            surf->format->Amask
        );
        SDL_Rect r = { x, y, w, h };
        SDL_BlitSurface(surf, &r, subs, nullptr);
        out->create(ctx, subs);
        return out;
    }

	SDL_Texture* Texture::use()
	{
		if (tex == nullptr) {
			std::cout << "(" << name << ") error: need to create texture first" << std::endl;
			//printf("creating texture\n");
			//tex = SDL_CreateTextureFromSurface(renderer, surf);
		}
		return tex;
	}

    void Texture::display(int x, int y)
    {
        Context& ctx = MyEngine::getContext();
        SDL_Rect r;
        r.x = x;
        r.y = y;
        r.w = w;
        r.h = h;

        SDL_RenderCopy(ctx.getRenderer(), use(), nullptr, &r);
    }

    SDL_Surface* Texture::getSurface()
    {
        return surf;
    }

    void Texture::setName(const std::string& str)
    {
        name = str;
    }

    std::string Texture::getName()
    {
        return name;
    }

	void Texture::destroy()
	{
        if (tex != nullptr)
        {
            SDL_DestroyTexture(tex);
            tex = nullptr;
        }
        if (surf != nullptr)
        {
            SDL_UnlockSurface(surf);
            SDL_FreeSurface(surf);
            surf = nullptr;
        }
	}
}
