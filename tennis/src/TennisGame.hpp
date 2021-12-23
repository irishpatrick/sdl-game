#ifndef TENNISGAME_HPP
#define TENNISGAME_HPP

#include "engine.hpp"

#include "TitleScreenState.hpp"
#include "MatchState.hpp"

using namespace engine;

class TennisGame : public StateBasedGame
{
public:
    TennisGame();

    virtual void init();
    
private:
    TitleScreenState state_titleScreen;
    MatchState state_match;
};

#endif /* TENNISGAME_HPP */
