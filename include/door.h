#ifndef DOOR_H
#define DOOR_H

#include <cstdint>
#include <string>
#include "sprite.h"
class GroupManager;

class Door: public Sprite
{
public:
    Door();
    ~Door();

    void SetManager(GroupManager*);
    void SetDest(const std::string&);
    void Enter();
    void OnCollision();

private:
    GroupManager* manager_;
    std::string dest_;
};

#endif /* DOOR_H */
