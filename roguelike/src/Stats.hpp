#pragma once

#define NUM_STATS 3
#define RES_STATS 1

class Stats
{
public:
    Stats();
    ~Stats();

    static const int ATK = 0;
    static const int DEF = 1;
    static const int SPD = 2;
    static const int HP = 3;

    void setStat(int, int);

    int getStat(int);
    int modStat(int, int);
    int resetStat(int);
    int resetStats();

    int getLvl();
    int getXp();
    int getHp();

    void giveXp(int);
    void modHp(int);

private:
    int lvl;
    int xp;
    int hp;
    int cur[NUM_STATS + RES_STATS];
    int mod[NUM_STATS];
};
