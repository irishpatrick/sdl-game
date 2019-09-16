#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Context.hpp"
//#include "Sprite.hpp"
//#include "State.hpp"

namespace engine
{
    class Sprite;
    class State;
    
    class MyEngine
    {
    public:
        static void addSprite(Sprite*);
        static void delSprite(Sprite*);
        
        static void addState(State*);
        static void delState(State*);
        static void delState(const std::string&);
        static State* getState(const std::string&);
        static void setCurrentState(const std::string&);
        static State* getCurrentState();
        static Context& getContext();
        static void printNum();

        //static Sprite* newSprite();

    private:
        //static std::vector<std::shared_ptr<Sprite>> sprites;
        static std::vector<Sprite*> sprites;
        static std::vector<State*> states;
        static State* currentState;
        static Context ctx;
    };
}