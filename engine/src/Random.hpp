#pragma once

namespace engine
{

class Random
{
public:
    static int randint(int, int);

private:
    static int seeded;
};

}
