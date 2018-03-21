#ifndef DOOR_H
#define DOOR_H

#include <cstdint>
#include <string>

#include <engine.h>

using namespace std;

class GroupManager;

class Door: public engine::Sprite
{
public:
    Door();
    ~Door();

    engine::Point* GetExit();
    void SetManager(GroupManager*);
    void SetDest(const string&);
    void SetExit(float, float);
    void Enter();
    void OnCollision(Sprite*) override;

    void setTag(const string&);
    string getTag();

private:
    GroupManager* manager_;
    string dest_;
    engine::Point exit_;
    string tag;
};

#endif /* DOOR_H */
