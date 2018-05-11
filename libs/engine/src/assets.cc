#include "assets.h"
#include "texture.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <boost/filesystem.hpp>
#include <sstream>
#include <iostream>

namespace engine {

std::map<std::string, Texture*> Assets::texMap = std::map<std::string, Texture*>();
std::vector<boost::future<void>> Assets::futures = std::vector<boost::future<void>>();

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

void Assets::loadTexture(const std::string& fn, SDL_Renderer* r)
{
    std::vector<std::string> vec = split(fn, '/');
    std::string key = vec[vec.size() - 1];

    /*if (texMap.find(key) != texMap.end()) {
        texMap[key] = new Texture(r);
        futures.push_back(std::async(std::launch::async, parallel_load, std::ref(texMap), fn, key));
    } else {
        std::cout << "key does not exist" << std::endl;
    }*/

    texMap[key] = new Texture(r);
    //futures.push_back(std::async(std::launch::async, parallel_load, std::ref(texMap), fn, key));
    futures.push_back(boost::async(boost::launch::async, boost::bind(parallel_load, std::ref(texMap), fn, key)));

}

void Assets::loadTexturesFromVector(const std::string& dir, std::vector<std::string> files, SDL_Renderer* r) {
    for (auto& e : files) {
        loadTexture(dir + e, r);
    }
}

void Assets::loadTexturesFromJson(const std::string& fn, const std::string& rootstr, SDL_Renderer* r) {
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

void Assets::getFutures()
{
    for (auto& e : futures)
    {
        e.get();
    }
    for (auto& e : texMap)
    {
        e.second->use();
    }
}

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
