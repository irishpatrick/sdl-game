#include "builder.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#define _USE_MATH_DEFINES
#include <cmath>

static bool seeded = false;

int r(int min, int max) {
    if (!seeded) {
        srand(time(nullptr));
        seeded = true;
    }
    //cout << "random(" << min << ", " << max << ")" << endl;
    return (rand() % (max - min)) + min;
}

Builder::Builder() {

}

Builder::~Builder() {

}

string Builder::genRoomInstruction(int x, int y, int w, int h) {
    return
        "R" +
        to_string(x) + "," +
        to_string(y) + "," +
        to_string(w) + "," +
        to_string(h) + "," +
        "E";
}

string Builder::genLoopMap() {
    vector<string> instructions;
    string ret;

    int radius = 6;
    // 4 rooms in primary loop
    for (int i=0;i<3;i++) {
        double a = M_PI / 2.0 * i;
        int x = radius * cos(a);
        int y = radius * sin(a);
        int w = r(2,6);
        int h = r(2,6);
        instructions.push_back(genRoomInstruction(x,y,w,h));
    }

    for (int i=1;i<3;i++) {
        
    }

    for (auto const& s : instructions) {
        ret += s;
    }

    return ret;
}
