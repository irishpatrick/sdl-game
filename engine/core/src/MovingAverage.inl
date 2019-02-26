#include "MovingAverage.hpp"

namespace engine
{
    template <typename T>
    MovingAverage<T>::MovingAverage()
    {
        array = nullptr;
        weight = nullptr;
    }

    template <typename T>
    MovingAverage<T>::~MovingAverage()
    {
        if (array != nullptr)
        {
            free(array);
        }

        if (weight != nullptr)
        {
            free(array);
        }
    }

    template <typename T>
    int MovingAverage<T>::allocate(size_t size)
    {
        len = size;
        array = (T*)malloc(size * sizeof(T));
        weight = (float*)malloc(size * sizeof(float));
        if (array == nullptr)
        {
            return 1;
        }
        if (weight == nullptr)
        {
            return 1;
        }
        return 0;
    }

    template <typename T>
    void MovingAverage<T>::shiftIn(T value)
    {
        for (size_t i=0; i<len-1; i++)
        {
            swapValue(i, i+1);
        }
        array[len-1] = value;
    }

    template <typename T>
    void MovingAverage<T>::shiftIn(T value, float w)
    {
        for (size_t i=0; i<len-1; i++)
        {
            swapValue(i, i+1);
            swapWeight(i, i+1);
        }
        array[len-1] = value;
        weight[len-1] = w;
    }

    template <typename T>
    float MovingAverage<T>::getAverage()
    {
        float sum = 0.0f;
        for (size_t i=0; i<len; ++i)
        {
            sum += array[i];
        }
        return (float)sum / (float)len;
    }

    template <typename T>
    float MovingAverage<T>::getWeightedAverage()
    {
        float sum = 0.0f;
        for (size_t i=0; i<len; ++i)
        {
            sum += array[i] * weight[i];
        }
        return (float)sum / (float)len;
    }

    template <typename T>
    void MovingAverage<T>::swapValue(size_t a, size_t b)
    {
        T tmp = array[a];
        array[a] = array[b];
        array[b] = tmp;
    }

    template <typename T>
    void MovingAverage<T>::swapWeight(size_t a, size_t b)
    {
        float tmp = weight[a];
        weight[a] = weight[b];
        weight[b] = tmp;
    }
}
