#ifndef MATCHSTATE_HPP
#define MATCHSTATE_HPP

#include "engine.hpp"

#include "Player.hpp"
#include "Opponent.hpp"
#include "Ball.hpp"
#include "Court.hpp"
#include "Stats.hpp"
#include "Scoreboard.hpp"

using namespace engine;

class MatchState : public State
{
public:
    MatchState();

    virtual void onEntry();
    virtual void init(Context&);
    virtual void update(float);
    virtual void render(Context&, float);
    virtual void destroy();

private:
    Stats stats;
    Player player;
    Opponent opponent;
    Ball ball;
    Court court;
    Scoreboard board;
};

#endif /* MATCHSTATE_HPP */
