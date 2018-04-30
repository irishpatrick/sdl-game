#pragma once

#include <string>

using namespace std;

class Builder {
public:
    Builder();
    ~Builder();

    string genLoopMap();
    string genRoomInstruction(int,int,int,int);
};
