#include "animation.h"

Animation::Animation()
{
    tex_ = nullptr;
    currentset_ = nullptr;
}

Animation::~Animation()
{
    printf("destroying...\n");
    for (auto& e: animations_)
    {
        free(e->frames);
        free(e->name);
        free(e);
    }

    for (auto& e: frames_)
    {
        free(e);
    }
}

SDL_Rect* Animation::GetCurrentFrame()
{
    return currentframe;
}

void Animation::InitFromJson(const std::string& fn)
{
    std::ifstream in(fn);
	nlohmann::json o;
	in >> o;
    in.close();

    tex_ = Assets::getTexture(o["texture"]);
    uint32_t w = o["width"];
    uint32_t h = o["height"];

    uint32_t cx = 0;
    uint32_t cy = 0;
    uint32_t n = (tex_->getH() / h) * (tex_->getW() / w);
    printf("%d\n", n);

    for (uint32_t i=0; i<n; i++)
    {
        SDL_Rect* r = (SDL_Rect*)malloc(sizeof(SDL_Rect));
        r->x = cx;
        r->y = cy;
        r->w = w;
        r->h = h;

        frames_.push_back(r);

        cx = (i * w) % tex_->getW();
        if (cx == 0)
        {
            cy += h;
        }
    }

    printf("done with frames!\n");

    if (o.find("animations") != o.end())
    {
        for (auto& e : o["animations"])
        {
            FrameSet* fs = (FrameSet*)malloc(sizeof(FrameSet));
            std::string name = e["name"];
            uint32_t* ptr = (uint32_t*)malloc(e["frames"].size() * sizeof(uint32_t));
            for (uint32_t i=0; i<e["frames"].size(); i++)
            {
                ptr[i] = (uint32_t)e["frames"][i];
            }
            fs->name = (char*)malloc(name.size());
            printf("no problem!\n");
            strcpy(fs->name, name.c_str());
            printf("still no problem!\n");
            fs->frames = ptr;
            printf("frames ok!\n");
            fs->fps = e["fps"];
            printf("fps ok!\n");
            animations_.push_back(fs);
            printf("bye bye\n");
        }
    }
}

void Animation::Start(const std::string& name, bool loop)
{
    
}

