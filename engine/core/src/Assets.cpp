#include "Assets.hpp"
#include "Texture.hpp"
#include "Context.hpp"
#include "Util.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace engine
{

	std::map<std::string, Texture*> Assets::texMap = std::map<std::string, Texture*>();
	Texture* Assets::missing = nullptr;
	fs::path Assets::cwd = fs::path();

	std::vector<std::string> Assets::split(const std::string& s, char delim)
	{
		std::stringstream ss(s);
		std::string item;
		std::vector<std::string> tokens;
		while (std::getline(ss, item, delim)) {
			tokens.push_back(item);
		}
		return tokens;
	}

	void Assets::getMissingTexture(Context& ctx)
	{
		if (missing != nullptr)
		{
			return;
		}
		uint32_t rmask, gmask, bmask, amask, magenta;
		#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			rmask = 0xff000000;
			gmask = 0x00ff0000;
			bmask = 0x0000ff00;
			amask = 0x000000ff;
			magenta = 0xff00ffff;
		#else
			rmask = 0x000000ff;
			gmask = 0x0000ff00;
			bmask = 0x00ff0000;
			amask = 0xff000000;
			magenta = 0xffff00ff;
		#endif
		Texture* t = new Texture();
		SDL_Surface* s = SDL_CreateRGBSurface(0, 32, 32, 32, rmask, gmask, bmask, amask);

		if (s == nullptr)
		{
			std::cout << "getMissingTexture error" << std::endl;
			exit(1);
		}

		for (uint32_t i=0; i<32*32; i++)
		{
			uint32_t* target = (uint32_t*)s->pixels + i;
			*target = magenta;
		}

		t->create(ctx, s);

		missing = t;
	}

	void Assets::loadTexture(Context& ctx, const std::string& fn)
	{
		std::cout << "loading texture " << fn << std::endl;
		std::vector<std::string> vec = split(fn, '/');
		std::string key = vec[vec.size() - 1];

		/*if (texMap.find(key) != texMap.end()) {
			texMap[key] = new Texture(r);
			futures.push_back(std::async(std::launch::async, parallel_load, std::ref(texMap), fn, key));
		} else {
			std::cout << "key does not exist" << std::endl;
		}*/

		Texture* t = new Texture();
		texMap[key] = t;
		t->setName(key);

		SDL_Surface* s = IMG_Load(fn.c_str());
		if (s == nullptr)
		{
			std::cout << "error!" << std::endl;
			std::cout << "t has been deleted" << std::endl;
			std::cout << "surface for " << t->getName() << " failed to load: " << IMG_GetError() << std::endl;
			delete t;
			return;
		}
		else
		{
			t->create(ctx, s);
		}

		SDL_FreeSurface(s);
	}

	void Assets::loadTexturesFromVector(const std::string& dir, std::vector<std::string> files, Context& ctx)
	{
		for (auto& e : files) {
			loadTexture(ctx, dir + e);
		}
	}

	void Assets::loadTexturesFromJson(Context& ctx, const std::string& fn)
	{
		// read json file
		fs::path pfn(fn);
		std::ifstream in(fn);
		if (in.fail())
		{
			std::cout << "cannot open " << fn << std::endl;
			return;
		}

		// parse into object
		nlohmann::json o;
		try
		{
			in >> o;
		}
		catch(std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}

		// set current working directory
		fs::path dir(o["dir"].get<std::string>());

		// load textures
		for (auto& current : o["files"])
		{
			std::string texfile = current.get<std::string>();
			std::string fn = current;
			loadTexture(ctx, (cwd / dir / fn).generic_string());
		}
	}

	Texture* Assets::getTexture(const std::string& key)
	{
		if (texMap.find(key) == texMap.end())
		{
			printf("key %s not found!\n", key.c_str());
			//getMissingTexture(ctx);
			//return missing;
			return nullptr;
		}
		if (texMap[key] == nullptr)
		{
			std::cout << "severe error: Assets::getTexture returned nullptr" << std::endl;
		}
		return texMap[key];
	}

	void Assets::useAll(Context& ctx)
	{

		for (auto& e : texMap)
		{
			std::cout << "querying " << e.second->getName() << std::endl;
			e.second->create(ctx);
			e.second->use();
		}
	}

	void Assets::destroy() {

		for (auto& e : texMap) {
			Texture* t = e.second;
			t->destroy();
			delete t;
		}
	}

	void Assets::setCwd(const std::string& dir)
	{
		cwd = fs::path(dir);
	}

	void Assets::setCwd(fs::path p)
	{
		cwd = p;
	}

}
