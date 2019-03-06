#include "Sprite.hpp"
#include "Group.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include <iostream>
#include <cairo.h>

namespace engine
{

	Sprite::Sprite()
	{
		x = 0;
		y = 0;
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
		tag = boost::uuids::random_generator()();
		collision_ = nullptr;
		camera = nullptr;
		uuid_str = "";
		boundingBox.x = 0.0f;
		boundingBox.y = 0.0f;
		boundingBox.w = -1.0f;
		boundingBox.h = -1.0f;
        debug = false;
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
            if (!isOnScreen(camera))
            {
                return;
            }
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

	void Sprite::draw(Camera& c, Context& ctx)
	{
		if (!visible) return;

        if (!isOnScreen(&c))
        {
            return;
        }

		if (texture == nullptr)
		{
			std::cout << "error, texture is null" << std::endl;
			return;
		}

        SDL_Rect rect;
		rect.x = x - c.x;
		rect.y = y - c.y;
		rect.w = w;
		rect.h = h;

		SDL_RenderCopy(ctx.getRenderer(), texture->use(), nullptr, &rect);
        if (debug)
        {
            debugDraw(c, ctx);
        }
    }

	void Sprite::debugDraw(Camera& camera, Context& ctx)
	{
        if (!canvas.isReady())
        {
            canvas.create(ctx, w, h);
            return;
        }

        cairo_t* cr = canvas.getCairo();

        cairo_rectangle(cr, 0, 0, 1, 1);
        cairo_set_source_rgba(cr, 1, 0, 1, 0.5);
        cairo_fill(cr);
	}

	void Sprite::setBoundingBox(int bx, int by, int bw, int bh) {
		boundingBox.x = (float)bx;
		boundingBox.y = (float)by;
		boundingBox.w = (float)bw;
		boundingBox.h = (float)bh;
	}

	BoundingBox& Sprite::getRelativeBoundingBox()
	{
		if (boundingBox.w == -1) {
			boundingBox.w = (float)w;
		}
		if (boundingBox.h == -1) {
			boundingBox.h = (float)h;
		}

		return boundingBox;
	}

	BoundingBox& Sprite::getBoundingBox()
	{
		realBoundingBox.x = x + boundingBox.x;
		realBoundingBox.y = y + boundingBox.y;
		realBoundingBox.w = boundingBox.w;
		realBoundingBox.h = boundingBox.h;
		if (boundingBox.w == -1) {
			realBoundingBox.w = (float)w;
		}
		if (boundingBox.h == -1) {
			realBoundingBox.h = (float)h;
		}

		return realBoundingBox;
	}

	Texture* Sprite::getTexture()
	{
		return texture;
	}

	void Sprite::setSolid(bool b)
	{
		solid = b;
	}

	bool Sprite::isSolid()
	{
		return solid;
	}

	void Sprite::SetVisible(bool b)
	{
		visible = b;
	}

	bool Sprite::IsVisible()
	{
		return visible;
	}

	void Sprite::setVisible(bool b)
	{
		visible = b;
	}

    void Sprite::setDebug(bool state)
    {
        debug = state;
    }

	bool Sprite::isVisible()
	{
		return visible;
	}

    bool Sprite::isOnScreen(Camera* c)
    {
        BoundingBox a = c->getViewport();
        BoundingBox b(x, y, w, h);
        return a.isInside(b);
    }

	void Sprite::setMaxSpeed(float a)
	{
		maxSpeed = a;
	}

	float Sprite::getMaxSpeed()
	{
		return maxSpeed;
	}

	std::string& Sprite::getName()
	{
		return name;
	}
}
