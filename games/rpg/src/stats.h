#ifndef STATS_H
#define STATS_H

#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <cstdint>
#include <fstream>
#include <streambuf>
#include <nlohmann/json.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using json = nlohmann::json;

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

    void load(const string&);
    void write(const string&);


private:
    map<string, uint32_t> stats;
    map<string, uint32_t> modifiers;
};

#endif /* STATS_H */
