#pragma once

#include <cstdlib>
#include <string>

class Snapshot
{
public:
    Snapshot();
    ~Snapshot();

    int allocate(size_t);
    void shiftIn(long);
    void setWeight(float, int);
    float getAverage();
    std::string string();

private:
    void swap(int, int);
    size_t len;
    long* array;
    float* weight;
};
