#ifndef DOOR_H
#define DOOR_H

#include <cstdint>
#include <string>

#include <engine.h>

class GroupManager;

class Door: public Sprite
{
public:
    Door();
    ~Door();

    Point* GetExit();

    void SetManager(GroupManager*);
    void SetDest(const std::string&);
    void SetExit(float, float);
    void Enter();
    void OnCollision(Sprite*);

private:
    GroupManager* manager_;
    std::string dest_;
    Point exit_;
};

#endif /* DOOR_H */
