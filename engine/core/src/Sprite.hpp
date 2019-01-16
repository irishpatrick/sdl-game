#pragma once

#include "core_api.hpp"

#include <string>
#include <cstdint>
#include <SDL.h>
#include <SDL_image.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "Context.hpp"
#include "BoundingBox.hpp"

namespace engine
{

    //class Animation;
    class Group;
    class Texture;
    class Camera;

    class Sprite
	{
    public:
    	CORE_API Sprite();
    	CORE_API virtual ~Sprite();

		CORE_API virtual void init(Context&);
        //CORE_API virtual Animation* getAnimation();
    	//CORE_API virtual void InitAnimation(const std::string&);
    	CORE_API virtual void setTexture(Texture*);
    	CORE_API virtual void draw(SDL_Renderer*);
        CORE_API virtual void draw(Context&);
		CORE_API virtual void draw(Camera&, Context&);
		//CORE_API virtual void draw(Object&, Context&);
    	CORE_API virtual void ResetCollision();
    	CORE_API virtual void update(float);
    	CORE_API void setSpeed(float);
    	CORE_API void queryTexture();
    	CORE_API virtual void OnCollision(Sprite*);
    	CORE_API Sprite* GetCollision();
    	CORE_API virtual void setParent(Group*);
    	CORE_API virtual Group* getParent();
    	CORE_API void setCamera(Camera*);
		CORE_API void setBoundingBox(int, int, int, int);
		CORE_API BoundingBox& getRelativeBoundingBox();
		CORE_API BoundingBox& getBoundingBox();

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

    	CORE_API std::string getUUID();

        float xvel;
        float yvel;
        float speed;
        float maxSpeed;
        Texture* texture;
        bool solid;
        std::string name;
        //Animation* anim;
		int w;
		int h;
		bool dynamic;
		float x;
		float y;

    protected:
        bool visible;
        Group* parent;
        Sprite* collision_;
        Camera* camera;
    	std::string uuid_str;
		BoundingBox boundingBox;
		BoundingBox realBoundingBox;

    private:
        boost::uuids::uuid tag;
    };

}
