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
        std::cout << "vector size: " << files.size() << std::endl;
		for (auto& e : files) {
            std::string path = (cwd / dir / e).generic_string();
            std::cout << "loading " << path << std::endl;
			loadTexture(ctx, path);
		}
	}

	void Assets::loadTexturesFromJson(Context& ctx, const std::string& fn)
	{
		// read json file
		json o = Util::loadJson(fn);

		// set current working directory
		fs::path dir(o["dir"].get<std::string>());

		// load textures
		for (auto& current : o["files"])
		{
			std::string texfile = current.get<std::string>();
			std::string cfn = current;
			loadTexture(ctx, (cwd / dir / cfn).generic_string());
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

    void Assets::registerTexture(Context& ctx, Texture& tex, const std::string& str)
    {
        if (texMap.find(str) == texMap.end())
        {
            Texture* t = new Texture(ctx, tex);
            texMap[str] = t;
        }
        else
        {
            std::cout << "pick a different texture id\n";
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
