#include "keyframesprite.hpp"
#include <fstream>
#include <experimental/filesystem>
#include <nlohmann/json.hpp>
#include <cstdlib>

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
		animations = (Anim*)malloc(sizeof(Anim) * o["animations"].size());
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
			c->fps = e["fps"];
			c->length = e["length"];
			c->frames = (int*)malloc(sizeof(int) * c->length);
			for (int i = 0; i < c->length; i++)
			{
				c->frames[i] = e["frames"][i];
			}
		}
	}
}