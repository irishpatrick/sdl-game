#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Config
{
public:
    static void loadFile(const std::string&);
    static int getScreenWidth();
    static int getScreenHeight();
    static std::string getAssetPath();
    static int getDrag();
    static int getPlaneSpeed();
    static int getMissileAcceleration();

private:
    static json o;
};

#endif /* CONFIG_H */
