#include "Sprite.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Group.hpp"
#include "Canvas.hpp"
#include "Util.hpp"
#include "Rect.hpp"
#include <iostream>
#include <cairo.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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
        //debug = false;
        collision_faces = 0;
        scale_x = 1.0f;
        scale_y = 1.0f;
        theta = 0;
        dynamic = false;
		sparent = nullptr;
	}

    Sprite::~Sprite()
    {

    }

	void Sprite::setSpeed(float s)
	{
		speed = s;
	}

	void Sprite::init(Context&)
	{

	}

	void Sprite::init(Context*)
	{

	}

    void Sprite::loadAnimation(const std::string& fn)
    {
        json o = Util::loadJson(fn);

        if (o.find("frames") == o.end())
        {

            return;
        }
        std::vector<Rect> frames;
        for (auto& e : o["frames"])
        {
            Rect r;
            r.x = e[0].get<int>();
            r.y = e[1].get<int>();
            r.w = e[2].get<int>();
            r.h = e[3].get<int>();
            frames.push_back(r);
        }

        if (o.find("animations") == o.end())
        {

            return;
        }
        for (auto& e : o["animations"])
        {
            Animation a;
            //a.setName(e[0].get<std::string>());
            a.setFps(e[1].get<int>());
            for (auto& f : e[2])
            {
                a.pushFrame(frames[f.get<int>()]);
            }
            animations[e[0].get<std::string>()] = a;
        }
    }

	void Sprite::update(float delta)
	{
		x += xvel * delta;
		y += yvel * delta;
        collision_faces = 0;

        updateChildren(delta);
	}

    void Sprite::update()
    {
        x += xvel;
        y += yvel;

        updateChildren();
    }

    void Sprite::update(Context& ctx, float delta)
    {
        update(delta);
        updateChildren(ctx, delta);
    }

	void Sprite::setTexture(Texture *t)
	{
		if (t == nullptr) {
			std::cout << "texture was null" << std::endl;
			return;
		}
		texture = t;
		w = texture->getW();
		h = texture->getH();
        boundingBox.w = (float)w;
        boundingBox.h = (float)h;
	}

	void Sprite::setCamera(Camera* c)
    {
		camera = c;
	}

	void Sprite::setParent(Group* g)
    {
		parent = g;
	}

	Group* Sprite::getParent()
    {
		return parent;
	}

	void Sprite::setSpriteParent(Sprite* s)
	{
		sparent = s;
	}

    void Sprite::addChild(Sprite* s)
    {
		s->setSpriteParent(this);
        children.push_back(s);
    }

    void Sprite::updateChildren(Context& ctx, float delta)
    {
        for (auto& e : children)
        {
            e->update(ctx, delta);
        }
    }

    void Sprite::updateChildren(float delta)
    {
        for (auto& e : children)
        {
            e->update(delta);
        }
    }

    void Sprite::updateChildren()
    {
        for (auto & e : children)
        {
            e->update();
        }
    }

	std::string Sprite::getUUID()
    {
		if (uuid_str == "") {
			uuid_str = boost::lexical_cast<std::string>(tag);
		}

		return uuid_str;
	}

    CORE_API void Sprite::translateX(float val)
    {
        x += val;
    }

    CORE_API void Sprite::translateY(float val)
    {
        y += val;
    }

	void Sprite::OnCollision(Sprite* sprite)
    {
		collision_ = sprite;
	}

	Sprite* Sprite::GetCollision()
    {
		return collision_;
	}

	void Sprite::ResetCollision()
    {
		collision_ = nullptr;
	}

	void Sprite::queryTexture()
    {
		w = texture->getW();
		h = texture->getH();
	}

    void Sprite::draw(Context& ctx)
    {
        if (!visible) return;
        drawChildren(ctx);
        if (texture == nullptr)
        {
	    std::cout << "error, texture is null" << std::endl;
	    return;
        }

        SDL_Rect rect;
	if (parent != nullptr)
        {
            rect.x = x + parent->getScreenX();
	    rect.y = y + parent->getScreenY();
        }
	else if (camera != nullptr)
        {
            if (!isOnScreen(camera))
            {
                return;
            }
	    rect.x = x + camera->x;
	    rect.y = y + camera->y;
	}
	else
        {
	    rect.x = x;
	    rect.y = y;
	}

        rect.w = w * scale_x;
        rect.h = h * scale_y;

        SDL_RenderCopyEx(
                ctx.getRenderer(),
                texture->use(),
                nullptr,
                &rect,
                theta,
                NULL,
                SDL_FLIP_NONE);
    }

    void Sprite::draw(Context& ctx, float e)
    {
        if (!visible) return;
        drawChildren(ctx);
        SDL_Rect r;
        r.x = x + (xvel * e);
        r.y = y + (yvel * e);
        r.w = w * scale_x;
        r.h = h * scale_y;

        SDL_RenderCopyEx(ctx.getRenderer(), texture->use(), nullptr, &r, theta, NULL, SDL_FLIP_NONE);
    }

    void Sprite::draw(Context& ctx, float e, Point offset)
    {
        if (!visible) return;
        drawChildren(ctx);
        SDL_Rect r;
        r.x = offset.x + x + (xvel * e);
        r.y = offset.y + y + (yvel * e);
        r.w = w * scale_x;
        r.h = h * scale_y;

        SDL_RenderCopyEx(ctx.getRenderer(), texture->use(), nullptr, &r, theta, NULL, SDL_FLIP_NONE);
    }

	void Sprite::draw(Context& ctx, Camera& c)
	{
        drawChildren(ctx, c);
		if (!visible) return;

        /*if (!isOnScreen(&c))
        {
            return;
        }*/

		if (texture == nullptr)
		{
			std::cout << "error, texture is null" << std::endl;
			return;
		}

        SDL_Rect rect;
		rect.x = x - c.x;
		rect.y = y - c.y;
		rect.w = w * scale_x;
		rect.h = h * scale_y;

		SDL_RenderCopy(ctx.getRenderer(), texture->use(), nullptr, &rect);
        /*if (debug)
        {
            debugDraw(c, ctx);
        }*/
    }

    void Sprite::drawChildren(Context& ctx)
    {
        for (auto& e : children)
        {
            e->draw(ctx, 0.0f, Point(x, y));
        }
    }

    void Sprite::drawChildren(Context& ctx, Camera& cam)
    {
        for (auto& e : children)
        {
            e->draw(ctx, cam);
        }
    }

    void Sprite::drawChildren(Context& ctx, float ex, Point offset)
    {
        for (auto& e : children)
        {
            e->draw(ctx, ex, offset);
        }
    }

	/*void Sprite::debugDraw(Camera& c, Context& ctx)
	{
        if (!canvas.isReady())
        {
            canvas.create(ctx, w, h);
            return;
        }

		canvas.x = x - c.x;
		canvas.y = y - c.y;

        cairo_t* cr = canvas.getCairo();

        cairo_set_source_rgba(cr, 0, 0.5, 1, 1);
        cairo_rectangle(cr, 0, 0, w, h);
        cairo_stroke(cr);

		cairo_set_source_rgba(cr, 1, 0, 1, 1);
		BoundingBox& b = getRelativeBoundingBox();
        cairo_rectangle(cr, b.x, b.y, b.w, b.h);
		cairo_stroke(cr);

		canvas.draw(ctx);
	}*/

	void Sprite::setBoundingBox(int bx, int by, int bw, int bh)
    {
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
		if (boundingBox.w == -1)
        {
			realBoundingBox.w = (float)w;
		}
		if (boundingBox.h == -1)
        {
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

    /*void Sprite::setDebug(bool state)
    {
        debug = state;
    }*/

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

    void Sprite::scale(float val)
    {
        scale_x = val;
        scale_y = val;
    }

    float Sprite::getScaledWidth()
    {
        return w * scale_x;
    }

    float Sprite::getScaledHeight()
    {
        return h * scale_y;
    }
}
