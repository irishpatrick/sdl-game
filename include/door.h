#ifndef DOOR_H
#define DOOR_H

#include <string>
class GroupManager;

class Door
{
public:
    Door();
    ~Door();

    void setmanager(GroupManager*);
    void setdest(const std::string&);
    void enter();

private:
    GroupManager* manager_;
    std::string dest_;
};

#endif /* DOOR_H */