#pragma once

namespace engine
{
    class Clock
    {
    public:
        Clock();
        ~Clock();

        void start();
        void tick();
        void lagTick();
        void back();

        double getDelta();
        double getLag();
        double extrapolate();

        static long getMillis();
        static long getNano();

        bool hasLag();

    private:
        int updateInterval;
        double cur;
        double elapsed;
        double prev;
        double lag;
        double back_ratio;
    };
}
