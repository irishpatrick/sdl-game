#include "Texture.hpp"

namespace engine
{

	Texture::Texture()
	{
		w = 0;
		h = 0;
		tex = NULL;
		surf = NULL;
		ready = false;
		name = "";
	}

    Texture::Texture(Context& ctx, const Texture& t)
    {
        w = t.w;
        h = t.h;
        ready = t.ready;
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
		w = t->getW();
		h = t->getH();
		tex = t->use();
		ready = true;
	}

	void Texture::create(Context& ctx)
	{
		tex = SDL_CreateTextureFromSurface(ctx.getRenderer(), surf);
		if (tex == nullptr) {
			std::cout << "(" << name << ") error: cannot create texture: " << SDL_GetError() << std::endl;
		}
	}

	void Texture::create(Context& ctx, SDL_Surface* s)
	{
		surf = s;
		tex = SDL_CreateTextureFromSurface(ctx.getRenderer(), s);
		if (tex == nullptr)
		{
			std::cout << "(" << name << ") error: " << SDL_GetError() << std::endl;
			return;
		}
		w = s->w;
		h = s->h;
		ready = true;
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

	SDL_Texture* Texture::use()
	{
		if (tex == nullptr) {
			std::cout << "(" << name << ") error: need to create texture first" << std::endl;
			//printf("creating texture\n");
			//tex = SDL_CreateTextureFromSurface(renderer, surf);
		}
		return tex;
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
		SDL_DestroyTexture(tex);
	}
}
