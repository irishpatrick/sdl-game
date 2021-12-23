#pragma once

#include "core_api.hpp"
#include "Context.hpp"
#include "Clock.hpp"

namespace engine
{
    class Game
    {
    public:
        CORE_API Game();
        CORE_API virtual ~Game();

        CORE_API virtual void init();
        CORE_API virtual void update();
        CORE_API virtual void draw(float);
        CORE_API virtual void loop();
        CORE_API virtual void start();
        CORE_API static void quit();

        inline Context& getContext()
        {
            return ctx;
        }

    protected:
        virtual void internalUpdate() {}
        virtual void internalDraw() {}

        Context ctx;
        Clock clock;
        static bool running;
    };
}
