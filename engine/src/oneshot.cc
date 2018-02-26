#include "oneshot.h"

OneShot::OneShot()
{
    state = false;
    reset = false;
}

OneShot::~OneShot()
{

}

void OneShot::check(bool b)
{
    if (reset)
    {
        state = false;
    }

    if (b && !reset)
    {
        state = true;
        reset = true;
    }

    if (!b && reset)
    {
        reset = false;
    }
}

bool OneShot::fire()
{
    return state;
}
