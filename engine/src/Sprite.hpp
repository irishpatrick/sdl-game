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
#include <map>

#include "Context.hpp"
#include "BoundingBox.hpp"
#include "Point.hpp"
#include "Animation.hpp"

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
        // constructors
        CORE_API Sprite();
        //CORE_API Sprite(const Sprite&);
        CORE_API virtual ~Sprite();

        // init
        CORE_API void init(Context&);
        CORE_API void init(Context*);

        // load
        CORE_API void loadAnimation(const std::string&);
        CORE_API void setTexture(Texture*);
        CORE_API void ResetCollision();

        // animations
        CORE_API void setCurrentAnimation(const std::string&);
        CORE_API void playAnimation();
        CORE_API void stopAnimation();
        CORE_API virtual void updateAnimations();

        // update
        CORE_API virtual void update(float);
        CORE_API virtual void update();
        CORE_API virtual void update(Context&, float);
        CORE_API void updateChildren(Context&, float);
        CORE_API void updateChildren(float);
        CORE_API void updateChildren();

        // draw
        CORE_API virtual void draw(Context&);
        CORE_API virtual void draw(Context&, float);
        CORE_API virtual void draw(Context&, float, Point);
        CORE_API virtual void draw(Context&, Camera&);
        CORE_API virtual void drawChildren(Context&);
        CORE_API virtual void drawChildren(Context&, Camera&);
        CORE_API virtual void drawChildren(Context&, float, Point);

        CORE_API void setSpeed(float);
        CORE_API void queryTexture();
        CORE_API void OnCollision(Sprite*);
        CORE_API Sprite* GetCollision();
        CORE_API void setParent(Group*);
        CORE_API Group* getParent();
        CORE_API void addChild(Sprite*);
        CORE_API void setSpriteParent(Sprite*);


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
        bool rejectCamera;
        //bool debug;
        Group* parent;
        Sprite* sparent;
        Sprite* collision_;
        Camera* camera;
        std::string uuid_str;
	    BoundingBox boundingBox;
	    BoundingBox realBoundingBox;
        std::vector<Sprite*> children;
        std::map<std::string, Animation> animations;
        std::string currentAnimation;

    private:
        boost::uuids::uuid tag;
    };

}
