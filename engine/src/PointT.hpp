#pragma once

namespace engine
{
    template <typename T>
    class PointT
    {
    public:
        PointT();
        ~PointT();

        T x;
        T y;
    };
}