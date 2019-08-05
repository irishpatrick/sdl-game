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

		// required field
		setTexture(Assets::getTexture(o["texture"].get<std::string>()));

		// not required
		if (o.find("animations") != o.end())
		{
			numAnimations = o["animations"].size();
			animations = std::vector<Anim>(numAnimations);
		}

		// required field
		int numFrames = o["frames"].size();
		frames = std::vector<Frame>(numFrames);

		currentAnim = 0;

		int n = 0;
		// everything is stored as an object {}
		if (verboseFormat)
		{
			for (auto& e : o["frameList"])
			{
				Frame* c = &frames[n++];
				c->x = e["x"];
				c->y = e["y"];
				c->w = e["w"];
				c->h = e["h"];
			}
		}
		// everything is stored as an array []
		else
		{
			for (auto& e : o["frames"])
			{
				Frame* c = &frames[n++];
				c->x = e[0];
				c->y = e[1];
				c->w = e[2];
				c->h = e[3];
			}
		}

		n = 0;
		if (numAnimations > 0)
		{
			// everything is stored as an object {}
			if (verboseFormat)
			{
				for (auto& e : o["animations"])
				{
					Anim* c = &animations[n++];

					// copy name
					size_t len = e["name"].get<std::string>().size();
					c->name = (char*)malloc(len);
					strncpy(c->name, e["name"].get<std::string>().c_str(), len);

					// fill fields
					c->fps = e["fps"];
					c->length = e["length"];
					c->frames = (int*)malloc(sizeof(int) * c->length);

					// fill frames
					for (int i = 0; i < c->length; i++)
					{
						c->frames[i] = e["frames"][i];
					}
				}
			}
			// everything is stored as an array []
			else
			{
				for (auto& e : o["animations"])
				{
					Anim* c = &animations[n++];
					size_t len = e[0].get<std::string>().size();
					c->name = (char*) malloc(len);
					strncpy(c->name, e[0].get<std::string>().c_str(), len);

					// fill fields
					c->fps = e[1];
					c->length = e[2];
					c->frames = (int*)malloc(sizeof(int) * c->length);

					// fill frames
					for (int i = 0; i < c->length; i++)
					{
						c->frames[i] = e[3][i];
					}
				}
			}
		}

		initialized = true;
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
			// check if valid name
			if (!strncmp(aname.c_str(), animations[i].name, strlen(animations[i].name)))
			{
				// set the current animation and set the proper timing
				currentAnim = i;
				timer.setInterval((long)((1.0f / animations[currentAnim].fps) * 1000));
				break;
			}
		}
		repeat = loop;
		running = true;
	}

    void KeyFrameSprite::setCurrentFrame(int frame)
    {
        running = false;
        currentFrame = frame;
    }

	void KeyFrameSprite::update(float delta)
	{
		Sprite::update(delta);

		if (!running || !initialized)
		{
			return;
		}

		if (animations.size() > 0)
		{
			if (animations[currentAnim].length == 0)
			{

			}
			else if (timer.tick())
			{
				if (currentFrame + 1 == animations[currentAnim].length)
				{
					// keep running if repeat is true
					// stop if false
					running = repeat;
				}
				frameIndex = (frameIndex + 1) % animations[currentAnim].length;
			}
		}
	}

    void KeyFrameSprite::update()
	{
		Sprite::update();

		if (!running || !initialized)
		{
			return;
		}
		if (animations.size() > 0)
		{
			if (animations[currentAnim].length == 0)
			{

			}
			else if (timer.tick())
			{
				if (frameIndex + 1 == animations[currentAnim].length)
				{
					running = repeat;
				}
				frameIndex = (frameIndex + 1) % animations[currentAnim].length;
			}

			currentFrame = animations[currentAnim].frames[frameIndex];
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
			Anim* ca = nullptr;
			if (animations.size() > 0)
			{
				ca = &animations[currentAnim];
			}
			Frame* cf = &frames[currentFrame];

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
