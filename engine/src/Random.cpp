#include "Random.hpp"

#include <cstdlib>
#include <ctime>

namespace engine
{

int Random::seeded = 0;

int Random::randint(int min, int max)
{
    if (!seeded)
    {
        srand(time(NULL));
        seeded = 1;
    }

    return (rand() % (max - min + 1)) + min;
}

}
