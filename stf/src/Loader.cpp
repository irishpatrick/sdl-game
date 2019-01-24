#include "Loader.hpp"
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace fs = std::experimental::filesystem;

namespace stf
{
    Loader::Loader()
    {
        currentSection = nullptr;
    }

    Loader::~Loader()
    {
        for (auto& e : sectionMap)
        {
            if (e.second != nullptr)
            {
                delete e.second;
            }
        }
    }

    void Loader::open(const std::string& fn)
    {
        std::ifstream fp;
        fp.open(fs::path(fn).generic_string());
        std::string line;
        std::vector<std::string> parts;
        std::string token;
        std::string delimiter = " ";
        while (std::getline(fp, line))
        {
            parts.clear();
            std::istringstream ss(line);
            while (std::getline(ss, token, ' '))
            {
                parts.push_back(token);
            }

            if (parts[0] == "begin")
            {
                currentSection = new Section();
                sectionMap[parts[1]] = currentSection;
            }

            if (parts[0] == "end")
            {

            }
        }
    }
}
