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
#include <vector>

#include "Context.hpp"
#include "BoundingBox.hpp"

#define FACE_NORTH 0x01
#define FACE_EAST 0x02
#define FACE_SOUTH 0x04
#define FACE_WEST 0x08

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

        CORE_API void init(Context&);
	CORE_API void init(Context*);
        CORE_API void setTexture(Texture*);
        CORE_API virtual void draw(Context&);
        CORE_API virtual void draw(Context&, float);
        CORE_API virtual void draw(Context&, Camera&);
        CORE_API virtual void drawChildren(Context&);
        CORE_API virtual void drawChildren(Context&, Camera&);
        CORE_API void ResetCollision();
    	CORE_API virtual void update(float);
        CORE_API virtual void update();
        CORE_API virtual void update(Context&, float);
        CORE_API void setSpeed(float);
    	CORE_API void queryTexture();
    	CORE_API void OnCollision(Sprite*);
    	CORE_API Sprite* GetCollision();
    	CORE_API void setParent(Group*);
    	CORE_API Group* getParent();
        CORE_API void addChild(Sprite*);
        CORE_API void updateChildren(Context&, float);
        CORE_API void updateChildren(float);

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
        CORE_API bool isOnScreen(Camera*);
	CORE_API void setMaxSpeed(float);
	CORE_API float getMaxSpeed();
	CORE_API std::string& getName();
        CORE_API std::string getUUID();
        CORE_API void translateX(float);
        CORE_API void translateY(float);
        CORE_API void scale(float);
        CORE_API float getScaledWidth();
        CORE_API float getScaledHeight();
	//CORE_API void debugDraw(Camera&, Context&);
        //CORE_API void setDebug(bool);
       
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
        float scale_x;
        float scale_y;
        float theta;
        unsigned char collision_faces;

    protected:
        bool visible;
        //bool debug;
        Group* parent;
        Sprite* collision_;
        Camera* camera;
        std::string uuid_str;
	    BoundingBox boundingBox;
	    BoundingBox realBoundingBox;
        std::vector<Sprite*> children;

    private:
        boost::uuids::uuid tag;
    };

}
