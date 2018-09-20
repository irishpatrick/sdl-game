#include "keyframesprite.hpp"
#include <fstream>
#include <experimental/filesystem>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <cstring>

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
		o << in;

		frameRef = (Frame*)malloc(sizeof(Frame) * o["frameList"].size());
		numAnimations = o["animations"].size();
		animations = (Anim*)malloc(sizeof(Anim) * numAnimations);
		currentAnim = o["default"];
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

		n = 0;
		for (auto& e : o["animations"])
		{
			Anim* c = &animations[n++];
			c->name = (char*)malloc(e["name"].size());
			strcpy(c->name, e[name].get<std::string>().c_str());
			c->fps = e["fps"];
			c->length = e["length"];
			c->frames = (int*)malloc(sizeof(int) * c->length);
			for (int i = 0; i < c->length; i++)
			{
				c->frames[i] = e["frames"][i];
			}
		}
	}

	void KeyFrameSprite::setCurrentAnimation(const std::string& name)
	{
		for (int i = 0; i < numAnimations; i++)
		{
			if (strncmp(name.c_str(), animations[i].name, strlen(animations[i].name)))
			{
				currentAnim = i;
				return;
			}
		}
	}

	void KeyFrameSprite::update(float delta)
	{
		timer.SetInterval(1.0f / animations[currentAnim].fps);

		if (timer.Tick())
		{
			currentFrame = (currentFrame + 1) % animations[currentAnim].length;
		}
		
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