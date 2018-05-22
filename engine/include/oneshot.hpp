#pragma once

#include <cstdio>

namespace engine {

class OneShot
{
public:
    OneShot();
    ~OneShot();

    void check(bool);
    bool fire();

private:
    bool state;
    bool reset;
};

}
