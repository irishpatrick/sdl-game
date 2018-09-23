#include "KeyFrameSprite.hpp"
#include <fstream>
#include <experimental/filesystem>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <cstring>
#include "Assets.hpp"

namespace fs = std::experimental::filesystem;
using json = nlohmann::json;

namespace engine
{
	void KeyFrameSprite::init(Context& ctx, const std::string& fn)
	{
		Sprite::init(ctx);

		fs::path fp(fn);
		std::ifstream in(fp.generic_string());
		if (in.fail())
		{
			std::cout << "cannot open " << fn << std::endl;
			return;
		}
		json o;

		try
		{
			o << in;
		}
		catch (json::parse_error& e)
		{
			std::cout << e.what() << std::endl;
		}

		setTexture(Assets::getTexture(o["texture"].get<std::string>()));
		frameRef = (Frame*)malloc(sizeof(Frame) * o["frameList"].size());
		numAnimations = o["animations"].size();
		animations = (Anim*)malloc(sizeof(Anim) * numAnimations);
		//currentAnim = o["default"];
		currentAnim = 0;
		int n;

		n = 0;
		for (auto& e : o["frameList"])
		{
			Frame* c = &frameRef[n++];
			c->x = e["x"];
			c->y = e["y"];
			c->w = e["w"];
			c->h = e["h"];
		}

		try
		{
			n = 0;
			for (auto& e : o["animations"])
			{
				Anim* c = &animations[n++];
				c->name = (char*)malloc(e["name"].get<std::string>().size());
				strcpy(c->name, e["name"].get<std::string>().c_str());
				c->fps = e["fps"];
				c->length = e["length"];
				c->frames = (int*)malloc(sizeof(int) * c->length);
				for (int i = 0; i < c->length; i++)
				{
					c->frames[i] = e["frames"][i];
				}
			}
		}
		catch (json::type_error& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	void KeyFrameSprite::setCurrentAnimation(const std::string& name, bool loop)
	{
		frameCount = 0;
		for (int i = 0; i < numAnimations; i++)
		{
			if (strncmp(name.c_str(), animations[i].name, strlen(animations[i].name)) == 0)
			{
				currentAnim = i;
				timer.SetInterval((1.0f / animations[currentAnim].fps) * 1000);
				break;
			}
		}
		repeat = loop;
		running = true;
	}

	void KeyFrameSprite::update(float delta)
	{
		Sprite::velocityUpdate(delta);

		if (!running)
		{
			return;
		}

		if (timer.Tick())
		{
			if (currentFrame + 1 == animations[currentAnim].length)
			{
				running = repeat;
			}
			currentFrame = (currentFrame + 1) % animations[currentAnim].length;
			Frame* fr = &frameRef[currentFrame];	
		}
	}

	void KeyFrameSprite::stop()
	{
		repeat = false;
	}

	void KeyFrameSprite::draw(Context& ctx)
	{
		if (!visible)
		{
			return;
		}
		Anim* ca = &animations[currentAnim];
		Frame* cf = &frameRef[ca->frames[currentFrame]];

		SDL_Rect src;
		src.x = cf->x;
		src.y = cf->y;
		src.w = cf->w;
		src.h = cf->h;

		SDL_Rect dst;
		dst.x = x;
		dst.y = y;
		dst.w = w;
		dst.h = h;

		SDL_RenderCopy(ctx.getRenderer(), texture->use(), &src, &dst);
	}
}
