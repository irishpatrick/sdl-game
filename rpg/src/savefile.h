#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include <engine.h>

using namespace std;

using json = nlohmann::json;

class SaveFile
{
public:
    static void AddSprite(engine::Sprite*);
    static void Write(const string&);
    static void Read(const string&);

private:
    static vector<engine::Sprite*> sprites_;
};

#endif /* SAVEFILE_H */
