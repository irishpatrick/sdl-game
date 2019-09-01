#include "Texture.hpp"
#include <iostream>

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

    void Texture::update(SDL_Surface* s)
    {
        if (s == nullptr)
        {
            std::cout << "error: surface was null" << std::endl;
            return;
        }
        if (tex == nullptr)
        {
            std::cout << "error: texture was null" << std::endl;
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

    /*void Texture::postCopy()
    {
        surf = nullptr;
        tex = nullptr;
    }*/
}
