#include "Door.hpp"
#include "GroupManager.hpp"

Door::Door(): engine::Sprite()
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

void Door::SetDest(const string& d)
{
    dest_ = d;
}

void Door::setTag(const string& s)
{
    tag = s;
}

string Door::getTag()
{
    return tag;
}

void Door::SetExit(float a, float b)
{
    exit_.set(a, b);
}

void Door::Enter()
{
    if (dest_ != "")
    {
        manager_->setActive(dest_);
        //manager_->setEntry(getTag());
    }
}

void Door::OnCollision(Sprite* sprite)
{
    Sprite::OnCollision(sprite);
    //Enter();
}

engine::Point* Door::GetExit()
{
    return &exit_;
}
