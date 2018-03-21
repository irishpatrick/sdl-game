#ifndef STATS_H
#define STATS_H

#include <iostream>
#include <map>
#include <string>
#include <cstdint>
#include "nlohmann/json.hpp"

using namespace std;

class Stats {
public:
    Stats();
    ~Stats();

    void reset();
    void modify(const string&, uint32_t);
    void change(const string&, uint32_t);
    void set(const string&, uint32_t);

    uint32_t get(const string&);
    uint32_t getBase(const string&);


private:
    map<string, uint32_t> stats;
    map<string, uint32_t> modifiers;
};

#endif /* STATS_H */
