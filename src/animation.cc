#include "animation.h"

Animation::Animation()
{
    tex_ = nullptr;
}

Animation::~Animation()
{
    for (auto& e: animmap_)
    {
        free(e.second);
    }
}

SDL_Rect* Animation::GetCurrentFrame()
{
    return currentframe;
}

void Animation::InitFromJson(const std::string& fn)
{
    std::ifstream i(fn);
	nlohmann::json o;
	i >> o;

    if (o.find("animations") != o.end())
    {
        for (auto& e : o["animations"])
        {
            std::string name = e["name"];
            uint32_t* ptr = (uint32_t*)malloc(o["frames"].size() * sizeof(uint32_t));
            animmap_.insert(std::pair<std::string, uint32_t*>(name, ptr));
        }
    }
}

