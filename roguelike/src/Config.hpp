#pragma once

#include <string>
#include <map>

class Config
{
public:
    static void load(const std::string&);
    static std::string getKey(const std::string&);

private:
    static std::map<std::string, std::string> keymap;
};