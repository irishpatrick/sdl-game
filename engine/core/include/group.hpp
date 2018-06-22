#pragma once

#include "core_api.hpp"

#include <vector>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>
#include <streambuf>

#include <SDL2/SDL.h>
#include <nlohmann/json.hpp>

#include "object.hpp"
#include "context.hpp"

namespace engine {

    class Sprite;
    class Camera;

    class Group : public Object {
    public:
        CORE_API Group();
        CORE_API ~Group();

        CORE_API void init(SDL_Renderer*);
        CORE_API void init_from_json(const std::string&);
        CORE_API void update(float);
        CORE_API void draw(SDL_Renderer*);
        CORE_API void draw(Context&);
        CORE_API void draw(Object&, Context&);
        CORE_API void destroy();
        CORE_API std::vector<Sprite*> getSprites();
        CORE_API void add(Sprite*);
        CORE_API void queryAll();
        CORE_API void sort();
        CORE_API Sprite* get_sprite_by_name(const std::string&);
        CORE_API Sprite* getSpriteAtLocation(float, float);
        CORE_API void remove(Sprite*);

        // defined in group.inl
        template <class T>
        void getSpritesByType(std::vector<T*>&);

        float sx;
        float sy;
    private:
        std::vector<Sprite*> renderList;
    };

}

#include "group.inl"
