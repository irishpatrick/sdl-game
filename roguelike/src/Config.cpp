#include "Config.hpp"
#include "Stuff.hpp"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

using json = nlohmann::json;

std::map<std::string, std::string> Config::keymap;

void Config::load(const std::string& fn)
{
    std::cout << "loading config: " << fn << std::endl;
    std::ifstream in(fn);
    if (!in)
    {
        return;
    }
    json o;
    in >> o;
    in.close();

    if (!json_has(o, "keys"))
    {
        std::cout << "no keys defined" << std::endl;
    }
    else
    {
        for (auto& e : o["keys"].items())
        {
            //std::cout << "registering key " << e.key() << " as " << e.value() << std::endl;
            keymap[e.key()] = e.value();
        }
    }
}

std::string Config::getKey(const std::string& name)
{
    if (keymap.find(name) == keymap.end())
    {
        std::cout << "cannot find key" << std::endl;
        return "";
    }
    //std::cout << "return " << keymap[name] << std::endl;
    return keymap[name];
}
