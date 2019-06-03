#pragma once

#include "core_api.hpp"

#include <vector>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>
#include <streambuf>
#include <SDL.h>
#include <nlohmann/json.hpp>

#include "Context.hpp"

namespace engine 
{
    class Sprite;
    class Camera;

    class Group 
	{
    public:
        CORE_API Group();
        CORE_API virtual ~Group();

		CORE_API virtual void init(Context&);
        CORE_API void init_from_json(const std::string&);
        CORE_API virtual void update(float);
        CORE_API virtual void draw(Context&);
        //CORE_API void draw(Object&, Context&);
        CORE_API void draw(Camera&, Context&);
        CORE_API void destroy();
        CORE_API std::vector<Sprite*> getSprites();
        CORE_API void add(Sprite*);
        CORE_API void add(Sprite&);
        CORE_API void queryAll();
        CORE_API void sort();
        CORE_API Sprite* get_sprite_by_name(const std::string&);
        CORE_API Sprite* getSpriteAtLocation(float, float);
        CORE_API void remove(Sprite*);
		CORE_API void setVisible(bool);
		CORE_API bool isVisible();
		CORE_API void setDebug(bool);

        // defined in group.inl
        template <class T>
        void getSpritesByType(std::vector<T*>&);

		CORE_API inline float getScreenX()
		{
			return sx;
		}

		CORE_API inline float getScreenY()
		{
			return sy;
		}

        float sx;
        float sy;
		bool dynamic;
		float x;
		float y;

    protected:
        std::vector<Sprite*> renderList;

	private:
		bool visible;
    };

}

// getSpritesByType
#include "Group.inl"
