#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <cstdint>
#include <SDL.h>
#include <SDL_image.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "entity.h"

class Animation;
class Group;
class Texture;

class Sprite: public Entity
{
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
	void queryTexture();
    virtual void OnCollision(Sprite*);
    Sprite* GetCollision();
    bool IsVisible();
    void SetVisible(bool);
    virtual void setParent(Group*);
    virtual Group* getParent();

    virtual const std::string getUUID();

    float xvel;
    float yvel;
    float speed;
    Texture* texture;
    bool solid;
    bool dynamic;
    std::string name;
    Animation* anim;
protected:
    bool visible_;
    Group* parent;
    Sprite* collision_;

private:
    boost::uuids::uuid tag;
};

#endif /* SPRITE_H */
