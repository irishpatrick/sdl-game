#include "Animation.hpp"
#include "Texture.hpp"
#include "Util.hpp"
#include "Timer.hpp"
#include "Assets.hpp"
#include <iostream>
#include <nlohmann/json.hpp>

namespace engine {

    Animation::Animation() {
        tex_ = nullptr;
        currentset_ = nullptr;
        running_ = false;
        looping_ = false;
        currentframe_ = nullptr;
        framewidth_ = 0;
        frameheight_ = 0;
        timer_ = new Timer();
        currentindex_ = 0;
    }

    Animation::~Animation() {
        delete timer_;
        int n = 0;
        for (auto& e: animations_) {
            free(e->frames);
            free(e->name);
            free(e);
        }

        for (auto& e: frames_) {
            free(e);
        }
    }

    Texture* Animation::GetTexture() {
        return tex_;
    }

    SDL_Rect* Animation::GetCurrentFrame() {
        return currentframe_;
    }

    uint32_t Animation::GetFrameWidth() {
        return framewidth_;
    }

    uint32_t Animation::GetFrameHeight() {
        return frameheight_;
    }

    void Animation::initFromJson(const std::string& fn) {
        std::cout << "load " << fn << " from json" << std::endl;

        std::ifstream in(fn);
        if (in.fail()) {
            printf("failed to open %s\n", fn.c_str());
            //exit(1);
            return;
        }
        nlohmann::json o;
        in >> o;
        in.close();

        tex_ = Assets::getTexture(o["texture"]);
        uint32_t w = o["width"];
        uint32_t h = o["height"];
        framewidth_ = w;
        frameheight_ = h;

        uint32_t cx = 0;
        uint32_t cy = 0;
        //uint32_t n = (tex_->getH() / h) * (tex_->getW() / w);
        uint32_t n = tex_->getW() / framewidth_;
        std::cout << "num frames in file: " << n << std::endl;

        // map all frames in the texture
        // single row, many columns
        for (uint32_t i=0; i<n; i++)
        {
            /*SDL_Rect* r = (SDL_Rect*)malloc(sizeof(SDL_Rect));
            r->x = cx;
            r->y = cy;
            r->w = w;
            r->h = h;

            frames_.push_back(r);

            cx += w;
            if (cx >= tex_->getW())
            {
                cx = 0;
                cy += h;
            }*/

            SDL_Rect* r = (SDL_Rect*)malloc(sizeof(SDL_Rect));
            r->x = cx;
            r->y = 0;
            r->w = framewidth_;
            r->h = frameheight_;

            frames_.push_back(r);

            cx += framewidth_;
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
                fs->count = e["frames"].size();
                fs->name = (char*)malloc(name.size());
                strncpy(fs->name, name.c_str(), name.size());
                fs->frames = ptr;
                fs->fps = e["fps"];
                animations_.push_back(fs);
            }
        }

        currentframe_ = frames_[0];
    }

    void Animation::Start(const std::string& name, bool loop)
    {
        if (!running_)
        {
            looping_ = loop;
            FrameSet* current = nullptr;
            for (auto& e : animations_)
            {
                /*if (strcmp(e->name, name.c_str()) == 0) {
                    current = e;
                }*/
                if (e->name == name) {
                    current = e;
                }
            }
            if (current == nullptr)
            {
                printf("animation not found!\n");
                return;
            }

            // calculate ms from fps
            timer_->setInterval(1.0/(double)current->fps*1000.0);
            currentindex_ = current->frames[0];
            currentset_ = current;
            running_ = true;
        }
    }

    void Animation::Update()
    {
        if (running_)
        {
            currentframe_ = frames_[currentset_->frames[currentindex_]];
            if (timer_->tick())
            {
                currentindex_++;
                if (currentindex_ == currentset_->count)
                {
                    if (looping_)
                    {
                        currentindex_ = currentset_->frames[0];
                    }
                    else
                    {
                        running_ = false;
                    }
                }
            }
        }
    }

    void Animation::Stop()
    {
        looping_ = false;
    }

    void Animation::Kill()
    {
        running_ = false;
        looping_ = false;
    }

}
