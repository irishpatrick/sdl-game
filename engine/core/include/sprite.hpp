#pragma once

#include "core_api.hpp"

#include <string>
#include <cstdint>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "entity.hpp"
#include "context.hpp"

namespace engine {

    class Animation;
    class Group;
    class Texture;
    class Camera;

    // entity has x, y, w, h
    class Sprite: public Entity {
    public:
    	CORE_API Sprite();
    	CORE_API virtual ~Sprite();

		CORE_API virtual void init(Context&);
        CORE_API virtual Animation* GetAnimation();
    	CORE_API virtual void InitAnimation(const std::string&);
    	CORE_API virtual void setTexture(Texture*);
    	CORE_API virtual void draw(SDL_Renderer*);
        CORE_API virtual void draw(Context&);
    	CORE_API virtual void ResetCollision();
    	CORE_API virtual void update(float);
    	CORE_API virtual void velocityUpdate(float);
    	CORE_API void setSpeed(float);
    	CORE_API void queryTexture();
    	CORE_API virtual void OnCollision(Sprite*);
    	CORE_API Sprite* GetCollision();
    	CORE_API virtual void setParent(Group*);
    	CORE_API virtual Group* getParent();
    	CORE_API void setCamera(Camera*);
		CORE_API void setBoundingBox(int, int, int, int);
		
		CORE_API inline SDL_Rect& getBoundingBox() {
			realBoundingBox.x = x + boundingBox.x;
			realBoundingBox.y = y + boundingBox.y;
			realBoundingBox.w = boundingBox.w;
			realBoundingBox.h = boundingBox.h;
			if (boundingBox.w == -1) {
				realBoundingBox.w = w;
			}
			if (boundingBox.h == -1) {
				realBoundingBox.h = h;
			}

			return realBoundingBox;
		}

    	CORE_API inline Texture* getTexture() {
            return texture;
        }

    	CORE_API inline void setSolid(bool b) {
            solid = b;
        }

    	CORE_API inline bool isSolid() {
            return solid;
        }

    	CORE_API inline void SetVisible(bool b) {
            visible = b;
        }

    	CORE_API inline bool IsVisible() {
            return visible;
        }

    	CORE_API inline void setMaxSpeed(float a) {
            maxSpeed = a;
        }

    	CORE_API inline float getMaxSpeed() {
            return maxSpeed;
        }

    	CORE_API inline std::string getName() {
            return name;
        }

    	CORE_API virtual std::string getUUID();

        float xvel;
        float yvel;
        float speed;
        float maxSpeed;
        Texture* texture;
        bool solid;
        bool dynamic;
        std::string name;
        Animation* anim;
    protected:
        bool visible;
        Group* parent;
        Sprite* collision_;
        Camera* camera;
    	std::string uuid_str;
		SDL_Rect boundingBox;
		SDL_Rect realBoundingBox;

    private:
        boost::uuids::uuid tag;
    };

}
