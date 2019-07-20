#include "Random.hpp"

int Random::seeded = 0;

#include <cstdlib>
#include <ctime>

int Random::randint(int min, int max)
{
    if (!seeded)
    {
        srand(time(NULL));
        seeded = 1;
    }

    return (rand() % (max - min + 1)) + min;
}