#ifndef DOOR_H
#define DOOR_H

#include <cstdint>
#include <string>
class GroupManager;

class Door
{
public:
    Door();
    ~Door();

    void SetManager(GroupManager*);
    void SetDest(const std::string&);
    void Enter();

    float x;
    float y;
    uint32_t w;
    uint32_t h;

private:
    GroupManager* manager_;
    std::string dest_;
};

#endif /* DOOR_H */