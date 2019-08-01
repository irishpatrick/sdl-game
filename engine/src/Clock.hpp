#pragma once

namespace engine
{
    class Clock
    {
    public:
        Clock() :
            updateInterval(12),
            cur(0),
            prev(0),
            elapsed(0),
            lag(0)
        {}

        ~Clock();

        void start();
        void tick();
        void lagTick();
        
        double getDelta();
        double getLag();
        double extrapolate();

        bool hasLag();

    private:
        int updateInterval;
        double cur;
        double elapsed;
        double prev;
        double lag;
    };
}
