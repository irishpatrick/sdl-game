#include "KeyFrameSprite.hpp"
#include <fstream>
#include <experimental/filesystem>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <cstring>
#include "Assets.hpp"
#include "Util.hpp"

namespace fs = std::experimental::filesystem;
using json = nlohmann::json;

namespace engine
{
	void KeyFrameSprite::init(Context& ctx, const std::string& fn)
	{
		Sprite::init(ctx);

		initialized = false;

		json o = Util::loadJson(fn);

		std::string fmt = o["dataFormat"].get<std::string>();
		bool verboseFormat = fmt == "verbose";
		//std::cout << verboseFormat << std::endl;

		setTexture(Assets::getTexture(o["texture"].get<std::string>()));
		numAnimations = o["animations"].size();
		int numFrames = o["frameList"].size();
		animations = std::vector<Anim>(numAnimations);
		frameRef = std::vector<Frame>(numFrames);
		currentAnim = 0;
		int n;

		n = 0;
		if (verboseFormat)
		{
			for (auto& e : o["frameList"])
			{
				Frame* c = &frameRef[n++];
				c->x = e["x"];
				c->y = e["y"];
				c->w = e["w"];
				c->h = e["h"];
			}
		}
		else
		{
			for (auto& e : o["frameList"])
			{
				Frame* c = &frameRef[n++];
				c->x = e[0];
				c->y = e[1];
				c->w = e[2];
				c->h = e[3];
			}
		}

		try
		{
			n = 0;
			if (verboseFormat)
			{
				for (auto& e : o["animations"])
				{
					Anim* c = &animations[n++];
					c->name = (char*)malloc(e["name"].get<std::string>().size());
					// leak
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
			else
			{
				for (auto& e : o["animations"])
				{
					Anim* c = &animations[n++];
					c->name = (char*) malloc(e[0].get<std::string>().size());
					strcpy(c->name, e[0].get<std::string>().c_str());
					c->fps = e[1];
					c->length = e[2];
					c->frames = (int*)malloc(sizeof(int) * c->length);
					for (int i = 0; i < c->length; i++)
					{
						c->frames[i] = e[3][i];
					}
				}
			}
		}
		catch (std::exception& e)
		{
			std::cout << "exception thrown" << std::endl;
			std::cout << e.what() << std::endl;
		}

		initialized = true;

		setCurrentAnimation(o["default"].get<std::string>(), true);
	}

	void KeyFrameSprite::setCurrentAnimation(const std::string& aname, bool loop)
	{
		if (!initialized)
		{
			return;
		}
		frameCount = 0;
		for (int i = 0; i < numAnimations; i++)
		{
			// leak
			if (strncmp(aname.c_str(), animations[i].name, strlen(animations[i].name)) == 0)
			{
				currentAnim = i;
				timer.setInterval((long)((1.0f / animations[currentAnim].fps) * 1000));
				break;
			}
		}
		repeat = loop;
		running = true;
	}

	void KeyFrameSprite::update(float delta)
	{
		Sprite::update(delta);

		if (!running || !initialized)
		{
			return;
		}

		if (animations[currentAnim].length == 0)
		{

		}
		else if (timer.tick())
		{
			if (currentFrame + 1 == animations[currentAnim].length)
			{
				running = repeat;
			}
			currentFrame = (currentFrame + 1) % animations[currentAnim].length;
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

		SDL_Rect src, dst;

		if (initialized)
		{
			Anim* ca = &animations[currentAnim];
			Frame* cf = &frameRef[ca->frames[currentFrame]];

			w = cf->w;
			h = cf->h;
			setBoundingBox(0, 0, w, h);

			src.x = (int)cf->x;
			src.y = (int)cf->y;
			src.w = (int)cf->w;
			src.h = (int)cf->h;

			dst.x = (int)x;
			dst.y = (int)y;
			dst.w = (int)cf->w;
			dst.h = (int)cf->h;

			SDL_RenderCopy(ctx.getRenderer(), texture->use(), &src, &dst);
		}		
	}
}
