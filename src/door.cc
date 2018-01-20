#include "door.h"
#include "groupmanager.h"

Door::Door()
{
    dest_ = "";
    manager_ = nullptr;
    x = 0.0;
    y = 0.0;
}

Door::~Door()
{

}

void Door::SetManager(GroupManager* m)
{
    manager_ = m;
}

void Door::SetDest(const std::string& d)
{
    dest_ = d;
}

void Door::Enter()
{
    if (dest_ != "")
    {
        manager_->setactive(dest_);
    }
}