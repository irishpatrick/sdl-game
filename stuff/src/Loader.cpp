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
                std::cout << "delete section" << std::endl;
                delete e.second;
            }
        }
    }

    Section& Loader::getSection(const std::string& id)
    {
        return *sectionMap[id];
    }

    void Loader::open(const std::string& fn)
    {
        std::ifstream fp;
        fp.open(fs::path(fn).generic_string());
        if (!fp.is_open())
        {
            std::cout << "error opening file " << fn << std::endl;
            return;
        }
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
                std::cout << "new section: " << parts[1] << std::endl;
                currentSection = new Section(parts[1]);
                sectionMap[parts[1]] = currentSection;
                continue;
            }

            if (parts[0] == "end")
            {
                std::cout << "end section" << std::endl;
				currentSection = nullptr;
                continue;
            }

            if (currentSection != nullptr)
            {
                std::cout << "add line: " << line << std::endl;
                currentSection->addLine(line);
                continue;
            }
        }
    }
}
