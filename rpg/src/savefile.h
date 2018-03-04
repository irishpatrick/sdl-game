#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include <engine.h>

using json = nlohmann::json;

class SaveFile
{
public:
    static void AddSprite(Sprite*);
    static void Write(const std::string&);
    static void Read(const std::string&);

private:
    static std::vector<Sprite*> sprites_;
};

#endif /* SAVEFILE_H */
