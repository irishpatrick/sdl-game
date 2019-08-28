#pragma once

class Stats
{
public:
    Stats();
    ~Stats();

    int getLvl();
    int getXp();
    int getHp();
    int getAtk();
    int getDef();
    int getSpd();

    void giveXp(int);

private:
    int lvl;
    int xp;
    int hp;
    int atk;
    int def;
    int spd;
};