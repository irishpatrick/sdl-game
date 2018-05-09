#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <cstdint>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "entity.h"

namespace engine {

class Animation;
class Group;
class Texture;
class Camera;

// entity has x, y, w, h
class Sprite: public Entity {
public:
    Sprite();
    virtual ~Sprite();

    virtual void InitAnimation(const std::string&);
    virtual void setTexture(Texture*);
    virtual void loadTexture(const std::string&, SDL_Renderer*);
    virtual void draw(SDL_Renderer*);
    virtual Animation* GetAnimation();
    virtual void ResetCollision();
    virtual void update(float);
    virtual void velocityUpdate(float);
    void setSpeed(float);
	void queryTexture();
    virtual void OnCollision(Sprite*);
    Sprite* GetCollision();
    virtual void setParent(Group*);
    virtual Group* getParent();
    void setCamera(Camera*);

    inline Texture* getTexture() {
        return texture;
    }

    inline void setSolid(bool b) {
        solid = b;
    }

    inline bool isSolid() {
        return solid;
    }

    inline void SetVisible(bool b) {
        visible_ = b;
    }

    inline bool IsVisible() {
        return visible_;
    }

    inline void setMaxSpeed(float a) {
        maxSpeed = a;
    }

    inline float getMaxSpeed() {
        return maxSpeed;
    }

    inline std::string getName() {
        return name;
    }

    virtual const std::string getUUID();

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
    bool visible_;
    Group* parent;
    Sprite* collision_;
    Camera* camera;

private:
    boost::uuids::uuid tag;
};

}

#endif /* SPRITE_H */
