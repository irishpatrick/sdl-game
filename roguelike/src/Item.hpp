#pragma once

#include <string>
#include <vector>

class Item
{
public:
    Item();
    ~Item();

    void load(const std::string&);

private:
    std::string name;
    std::string type;
    std::vector<int> data;
};
