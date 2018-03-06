#include "door.h"
#include "groupmanager.h"

Door::Door(): Sprite()
{
    dest_ = "";
    tag = "";
    manager_ = nullptr;
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

void Door::setTag(const std::string& s)
{
    tag = s;
}

std::string Door::getTag()
{
    return tag;
}

void Door::SetExit(float a, float b)
{
    exit_.Set(a, b);
}

void Door::Enter()
{
    if (dest_ != "")
    {
        manager_->setactive(dest_);
        manager_->setEntry(getTag());
    }
}

void Door::OnCollision(Sprite* sprite)
{
    Sprite::OnCollision(sprite);
    //Enter();
}

Point* Door::GetExit()
{
    return &exit_;
}
