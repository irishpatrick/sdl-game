#include "texture.hpp"

namespace engine {

	Texture::Texture() {
		w = 0;
		h = 0;
		tex = NULL;
		surf = NULL;
		ready = false;
		name = "";
	}

	Texture::~Texture() {

	}

	uint32_t Texture::getW() {
		return w;
	}

	uint32_t Texture::getH() {
		return h;
	}

	void Texture::set(SDL_Surface* s) {
		surf = s;
		w = surf->w;
		h = surf->h;
		//printf("%d, %d\n", w, h);
		ready = true;
	}

	void Texture::copy(Texture* t) {
		w = t->getW();
		h = t->getH();
		tex = t->use();
		ready = true;
	}

	void Texture::create(Context& ctx) {
		tex = SDL_CreateTextureFromSurface(ctx.getRenderer(), surf);
	}

	SDL_Texture* Texture::use() {
		if (ready && tex == nullptr) {
			std::cout << "error: need to create texture first" << std::endl;
			//printf("creating texture\n");
			//tex = SDL_CreateTextureFromSurface(renderer, surf);
		}
		return tex;
	}

	void Texture::destroy() {
		SDL_DestroyTexture(tex);
	}

}
