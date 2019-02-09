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
    class Group;
    class Texture;
    class Camera;

    class Sprite
	{
    public:
    	CORE_API Sprite();
    	CORE_API virtual ~Sprite();

		CORE_API virtual void init(Context&);
    	CORE_API virtual void setTexture(Texture*);
        CORE_API virtual void draw(Context&);
		CORE_API virtual void draw(Camera&, Context&);
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
		CORE_API Texture* getTexture();
		CORE_API void setSolid(bool);
		CORE_API bool isSolid();
		CORE_API void setVisible(bool);
		CORE_API bool isVisible();
		CORE_API void SetVisible(bool);
		CORE_API bool IsVisible();
		CORE_API void setMaxSpeed(float);
		CORE_API float getMaxSpeed();
		CORE_API std::string& getName();
    	CORE_API std::string getUUID();

        float xvel;
        float yvel;
        float speed;
        float maxSpeed;
        Texture* texture;
        bool solid;
        std::string name;
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
