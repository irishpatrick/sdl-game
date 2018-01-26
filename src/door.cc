#include "door.h"
#include "groupmanager.h"

Door::Door(): Sprite()
{
    dest_ = "";
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

void Door::Enter()
{
    printf("going through door!\n");
    if (dest_ != "")
    {
        manager_->setactive(dest_);
    }
}

void Door::OnCollision(Sprite* sprite)
{
    Sprite::OnCollision(sprite);
    //Enter();
}
