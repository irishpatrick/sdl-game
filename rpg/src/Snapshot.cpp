#include "Snapshot.hpp"
#include <sstream>

Snapshot::Snapshot()
{
    array = nullptr;
}

Snapshot::~Snapshot()
{
    if (array != nullptr)
    {
        free(array);
    }

    if (weight != nullptr)
    {
        free(weight);
    }
}

int Snapshot::allocate(size_t size)
{
    len = size;
    array = (long*)malloc(size * sizeof(long));
    weight = (float*)malloc(size * sizeof(float));
    if (array == nullptr)
    {
        return 1;
    }
    if (weight == nullptr)
    {
        return 1;
    }
    for (size_t i=0; i<len; i++)
    {
        array[i] = 0;
        weight[i] = 1.0f;
    }
    return 0;
}

void Snapshot::shiftIn(long value)
{
    for (size_t i=0; i<len-1; i++)
    {
        swap(i, i+1);
    }
    array[len-1] = value;
}

void Snapshot::setWeight(float w, int i)
{
    weight[i] = w;
}

float Snapshot::getAverage()
{
    float sum = 0.0;
    for (size_t i=0; i<len; i++)
    {
        sum += array[i] * weight[i];
    }
    return (float)sum / (float)len;
}

void Snapshot::swap(int a, int b)
{
    long tmp = array[a];
    array[a] = array[b];
    array[b] = tmp;
}

std::string Snapshot::string()
{
    std::stringstream stream;

    stream << "[";
    for (size_t i=0; i<len; i++)
    {
        stream << array[i] << ", ";
    }
    stream << "]";

    return stream.str();
}
