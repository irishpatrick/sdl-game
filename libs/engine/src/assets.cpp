#include "assets.hpp"
#include "texture.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <boost/filesystem.hpp>
#include <sstream>
#include <iostream>

namespace engine {

std::map<std::string, Texture*> Assets::texMap = std::map<std::string, Texture*>();
//std::vector<boost::future<void>> Assets::futures = std::vector<boost::future<void>>();

std::vector<std::string> split(const std::string& s, char delim)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;
    while (std::getline(ss, item, delim))
    {
        tokens.push_back(item);
    }
    return tokens;
}

void parallel_load(
    std::map<std::string, Texture*>& map,
    const std::string& fn,
    const std::string& key)
{
    SDL_Surface* s = IMG_Load(fn.c_str());
    if (s == nullptr)
    {
        printf("surface failed to load!\n");
        exit(1);
    }
    map[key]->set(s);
}

void single_load(Texture* t, const std::string& fn) {
	SDL_Surface* s = IMG_Load(fn.c_str());
	if (s == nullptr) {
		std::cout << "surface " << fn << " failed to load" << std::endl;
		exit(1);
	}
	t->set(s);
}

void Assets::loadTexture(const std::string& fn, SDL_Renderer* r)
{
    std::vector<std::string> vec = split(fn, boost::filesystem::path::preferred_separator);
    std::string key = vec[vec.size() - 1];

    /*if (texMap.find(key) != texMap.end()) {
        texMap[key] = new Texture(r);
        futures.push_back(std::async(std::launch::async, parallel_load, std::ref(texMap), fn, key));
    } else {
        std::cout << "key does not exist" << std::endl;
    }*/

    texMap[key] = new Texture(r);
	parallel_load(texMap, fn, key);
	//single_load(texMap[key], fn);
    //futures.push_back(std::async(std::launch::async, parallel_load, std::ref(texMap), fn, key));
    //futures.push_back(boost::async(boost::launch::async, boost::bind(std::ref(parallel_load), std::ref(texMap), fn, key)));

}

void Assets::loadTexturesFromVector(const std::string& dir, std::vector<std::string> files, SDL_Renderer* r) {
	std::cout << "loading textures from vector..." << std::endl;
	for (auto& e : files) {
        loadTexture(dir + e, r);
    }
	std::cout << "done!" << std::endl;
}

void Assets::loadTexturesFromJson(const std::string& fn, const std::string& rootstr, SDL_Renderer* r) {
	std::cout << "loading textures from json..." << std::endl;
    std::ifstream in(rootstr + fn);
    nlohmann::json o;
    in >> o;

    boost::filesystem::path root(rootstr);
    boost::filesystem::path dir(o["dir"].get<std::string>());

    for (auto& current : o["files"]) {
        std::cout << "loading " << current << std::endl;
        boost::filesystem::path file(current.get<std::string>());
        boost::filesystem::path full = root / dir / file;
        loadTexture(full.string(), r);
    }
	std::cout << "done!" << std::endl;
}

Texture* Assets::getTexture(const std::string& key)
{
    if (texMap.find(key) == texMap.end())
    {
        printf("key %s not found!\n", key.c_str());
        return NULL;
    }
    return texMap[key];
}

void Assets::useAll() {
	for (auto& e : texMap) {
		e.second->use();
	}
}

/*void Assets::getFutures()
{
    for (auto& e : futures)
    {
        e.get();
    }
    for (auto& e : texMap)
    {
        e.second->use();
    }
}*/

void Assets::destroy()
{
    /*for (auto &e : futures)
    {
        e.get();
    }*/

    for (auto& e : texMap) {
        Texture* t = e.second;
        t->destroy();
        delete t;
    }
}

}
