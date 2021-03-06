#pragma once

#include <cstdint>
#include <string>

#include <engine.hpp>

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
    void OnCollision(Sprite*);

    void setTag(const string&);
    string getTag();

    inline string getDest()
	{
        return dest_;
    }

    inline engine::Point& getExit()
	{
        return exit_;
    }

private:
    GroupManager* manager_;
    string dest_;
    engine::Point exit_;
    string tag;
};
