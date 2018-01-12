#include "door.h"

Door::Door()
{
    dest_ = "";
    manager_ = nullptr;
}

Door::~Door()
{

}

void Door::setmanager(GroupManager* m)
{
    manager_ = m;
}

void Door::setdest(const std::string& d)
{
    dest_ = d;
}

void Door::enter()
{
    if (dest_ != "")
    {
        manager_->setactive(dest_);
    }
}