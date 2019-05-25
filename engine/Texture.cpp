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

	SDL_Texture* Texture::use()
	{
		if (tex == nullptr) {
			std::cout << "(" << name << ") error: need to create texture first" << std::endl;
			//printf("creating texture\n");
			//tex = SDL_CreateTextureFromSurface(renderer, surf);
		}
		return tex;
	}

	void Texture::destroy()
	{
		SDL_DestroyTexture(tex);
	}
}
