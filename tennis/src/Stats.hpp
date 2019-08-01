#pragma once

#include <engine.hpp>

using namespace engine;

class Stats
{
public:
    Stats() :
        m_playerScore(0),
        m_opponentScore(0),
        m_volley(0)
    {}

    ~Stats();

    void recordVolley();
    void resetVolley();

private:
    int m_playerScore;
    int m_opponentScore;
    int m_volley;
};