#include "assets.h"
#include "texture.h"

std::map<std::string, Texture*> Assets::texMap = std::map<std::string, Texture*>();
std::vector<std::future<void>> Assets::futures = std::vector<std::future<void>>();

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

    texMap[key] = new Texture(r);
    futures.push_back(std::async(std::launch::async, parallel_load, std::ref(texMap), fn, key));
}

Texture* Assets::getTexture(const std::string& key)
{
    if (texMap.find(key) == texMap.end())
    {
        printf("not found!\n");
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

    std::map<std::string, Texture*>::iterator it;
    for (it = texMap.begin(); it != texMap.end(); it++)
    {
        Texture* t = it->second;
        t->destroy();
        delete t;
    }
}