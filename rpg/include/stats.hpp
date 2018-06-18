#pragma once

#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <cstdint>
#include <fstream>
#include <streambuf>
#include <nlohmann/json.hpp>
#include <boost/algorithm/string.hpp>

using json = nlohmann::json;

class Stats {
public:
    Stats();
    ~Stats();

    void reset();
    void modify(const std::string&, uint32_t);
    void change(const std::string&, uint32_t);
    void set(const std::string&, uint32_t);

    uint32_t get(const std::string&);
    uint32_t getBase(const std::string&);

    void load(const std::string&);
    void write(const std::string&);


private:
    std::map<std::string, uint32_t> stats;
    std::map<std::string, uint32_t> modifiers;
};
