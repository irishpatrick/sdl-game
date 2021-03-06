#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include <engine.hpp>

using namespace std;
using json = nlohmann::json;

class SaveFile
{
public:
    static void AddSprite(engine::Sprite*);
    static void Write(const string&);
    static void Read(const string&);

private:
    static vector<engine::Sprite*> sprites;
};
