#include "Stats.hpp"
#include <cmath>

Stats::Stats() :
    hp(3)
{

}

Stats::~Stats()
{

}

void Stats::setStat(int index, int val)
{
    cur[index] = val;
}

int Stats::getStat(int index)
{
    return cur[index] + mod[index];
}

int Stats::modStat(int index, int val)
{
    mod[index] += val;
    return 0;
}

int Stats::resetStat(int index)
{
    mod[index] = 0;
    return 0;
}

int Stats::resetStats()
{
    int i;
    for (i = 0; i < NUM_STATS; ++i)
    {
        resetStat(i);
    }

    return 0;
}

int Stats::getLvl()
{
    return lvl;
}

int Stats::getXp()
{
    return xp;
}

int Stats::getHp()
{
    return hp;
}

void Stats::giveXp(int val)
{

}

void Stats::modHp(int val)
{
    int pre = hp + val;
    pre = (int)fmin(0, pre);
    pre = (int)fmax(pre, getStat(HP));
    hp = pre;
}
