#pragma once

#include "core_api.hpp"

#include <cstdlib>
#include <cstdint>
#include <string>

namespace engine
{
    template <typename T>
    class MovingAverage
    {
    public:
        CORE_API MovingAverage();
        CORE_API ~MovingAverage();

        CORE_API int allocate(size_t);
        CORE_API void shiftIn(T);
        CORE_API void shiftIn(T, float);
        CORE_API float getAverage();
        CORE_API float getWeightedAverage();

    private:
        void swapValue(size_t, size_t);
        void swapWeight(size_t, size_t);
        size_t len;
        T* array;
        float* weight;
    };
}

#include "MovingAverage.inl"
