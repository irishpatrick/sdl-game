#include "Stats.hpp"

Stats::Stats() :
    lvl(0),
    xp(0),
    hp(0),
    atk(0),
    def(0),
    spd(0)
{

}

Stats::~Stats()
{
    
}

void Stats::giveXp(int val)
{
    xp += val;
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

int Stats::getAtk()
{
    return atk;
}

int Stats::getDef()
{
    return def;
}

int Stats::getSpd()
{
    return spd;
}