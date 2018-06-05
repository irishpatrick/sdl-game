#include "sprite.hpp"
#include "animation.hpp"
#include "group.hpp"
#include "texture.hpp"
#include "camera.hpp"

namespace engine {

	Sprite::Sprite() {
		x = 0;
		y = 0;
		w = 0;
		h = 0;
		xvel = 0;
		yvel = 0;
		speed = 0;
		maxSpeed = 0;
		texture = nullptr;
		parent = nullptr;
		solid = true;
		dynamic = false;
		visible_ = true;
		name = "";
		anim = new Animation();
		tag = boost::uuids::random_generator()();
		collision_ = nullptr;
		camera = nullptr;
		uuid_str = "";
	}

	Sprite::~Sprite() {
		delete anim;
	}

	void Sprite::setSpeed(float s) {
		speed = s;
	}

	void Sprite::InitAnimation(const std::string& fn) {
		anim->InitFromJson(fn);
		w = anim->GetFrameWidth();
		h = anim->GetFrameHeight();
		texture = anim->GetTexture();
	}

	void Sprite::update(float delta) {
		if (!visible_) {
			return;
		}

		if (anim->GetTexture() != nullptr) {
			anim->Update();
		}
	}

	void Sprite::velocityUpdate(float delta) {
		x += xvel * delta;
		y += yvel * delta;
	}

	Animation* Sprite::GetAnimation() {
		return anim;
	}

	void Sprite::setTexture(Texture *t) {
		if (t == NULL) {
			printf("texture was null!\n");
			return;
		}
		texture = t;
		w = texture->getW();
		h = texture->getH();
	}

	void Sprite::loadTexture(const std::string& fn, SDL_Renderer* r) {
		/*SDL_Texture* t = IMG_LoadTexture(r, fn.c_str());
		//setTexture(IMG_LoadTexture(r, fn.c_str()));
		if (t == NULL)
		{
			printf("texture error: %s\n", IMG_GetError());
		}
		texture = new Texture();
		texture->set(t);*/
	}

	void Sprite::setCamera(Camera* c) {
		camera = c;
	}

	void Sprite::setParent(Group* g) {
		parent = g;
	}

	Group* Sprite::getParent() {
		return parent;
	}

	std::string Sprite::getUUID() {
		if (uuid_str == "") {
			uuid_str = boost::lexical_cast<std::string>(tag);
		}
	
		return uuid_str;
	}

	void Sprite::OnCollision(Sprite* sprite) {
		collision_ = sprite;
	}

	Sprite* Sprite::GetCollision() {
		return collision_;
	}

	void Sprite::ResetCollision() {
		collision_ = nullptr;
	}

	void Sprite::queryTexture() {
		w = texture->getW();
		h = texture->getH();
	}

	void Sprite::draw(SDL_Renderer* r) {
		if (!visible_) {
			return;
		}
		//printf("%x\n", texture->use());

		//printf("%d, %d\n", w, h);
		SDL_Rect rect;
		if (parent != NULL) {
			rect.x = x + parent->screenX();
			rect.y = y + parent->screenY();
		}
		else {
			rect.x = x;
			rect.y = y;
		}
		rect.w = w;
		rect.h = h;

		//if (texture->use() == nullptr) return;
		if (anim->GetTexture() != nullptr) {
			SDL_RenderCopy(r, texture->use(), anim->GetCurrentFrame(), &rect);
		}
		else {
			SDL_RenderCopy(r, texture->use(), NULL, &rect);
		}
	}

}
