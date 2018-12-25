#include "Sprite.hpp"
//#include "Animation.hpp"
#include "Group.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include <iostream>

namespace engine {

	Sprite::Sprite() : Object()
	{
		w = 0;
		h = 0;
		xvel = 0.0f;
		yvel = 0.0f;
		speed = 0.0f;
		maxSpeed = 0.0f;
		texture = nullptr;
		parent = nullptr;
		solid = false;
		visible = true;
		name = "";
		//anim = new Animation();
		tag = boost::uuids::random_generator()();
		collision_ = nullptr;
		camera = nullptr;
		uuid_str = "";
		boundingBox.x = 0.0f;
		boundingBox.y = 0.0f;
		boundingBox.w = -1.0f;
		boundingBox.h = -1.0f;
	}

	Sprite::~Sprite()
	{
		//delete anim;
	}

	void Sprite::setSpeed(float s)
	{
		speed = s;
	}

	void Sprite::init(Context&)
	{

	}

	/*void Sprite::InitAnimation(const std::string& fn)
	{
		//anim->initFromJson(fn);
		w = anim->GetFrameWidth();
		h = anim->GetFrameHeight();
		texture = anim->GetTexture();
	}*/

	void Sprite::update(float delta)
	{
		x += xvel * delta;
		y += yvel * delta;
	}

	/*Animation* Sprite::getAnimation()
	{
		return anim;
	}*/

	void Sprite::setTexture(Texture *t)
	{
		if (t == nullptr) {
			std::cout << "texture was null" << std::endl;
			return;
		}
		texture = t;
		w = texture->getW();
		h = texture->getH();
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

	void Sprite::draw(Object& obj, Context& ctx) {
		if (!visible) return;

		SDL_Rect rect;
		rect.x = x + obj.x;
		rect.y = y + obj.y;
		rect.w = w;
		rect.h = h;

		/*if (anim->GetTexture() != nullptr) {
			SDL_RenderCopy(ctx.getRenderer(), texture->use(), anim->GetCurrentFrame(), &rect);
		}
		else {
			SDL_RenderCopy(ctx.getRenderer(), texture->use(), nullptr, &rect);
		}*/

		SDL_RenderCopy(ctx.getRenderer(), texture->use(), nullptr, &rect);
	}

    void Sprite::draw(Context& ctx) {
        if (!visible) return;

		if (texture == nullptr)
		{
			std::cout << "error, texture is null" << std::endl;
			return;
		}

        SDL_Rect rect;
		if (parent != nullptr) {
			rect.x = x + parent->getScreenX();
			rect.y = y + parent->getScreenY();
		}
		else if (camera != nullptr) {
			rect.x = x + camera->x;
			rect.y = y + camera->y;
		}
		else {
			rect.x = x;
			rect.y = y;
		}
		rect.w = w;
		rect.h = h;

		/*if (anim->GetTexture() != nullptr) {
			SDL_RenderCopy(ctx.getRenderer(), texture->use(), anim->GetCurrentFrame(), &rect);
		}
		else {
			SDL_RenderCopy(ctx.getRenderer(), texture->use(), NULL, &rect);
		}*/

		SDL_RenderCopy(ctx.getRenderer(), texture->use(), nullptr, &rect);
    }

	void Sprite::draw(SDL_Renderer* r) {
		/*if (!visible) {
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
		}*/
	}

	void Sprite::setBoundingBox(int bx, int by, int bw, int bh) {
		boundingBox.x = (float)bx;
		boundingBox.y = (float)by;
		boundingBox.w = (float)bw;
		boundingBox.h = (float)bh;
	}
}
