#include "Loader.hpp"
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

namespace fs = std::experimental::filesystem;

namespace stf
{
    Loader::Loader()
    {
        currentSection = nullptr;
    }

    Loader::~Loader()
    {
        currentSection = nullptr;
        
        for (auto& e : sectionMap)
        {
            if (e.second != nullptr)
            {

                delete e.second;
            }
        }
    }

    Section& Loader::getSection(const std::string& id)
    {
        if (sectionMap[id] == nullptr)
        {
            std::cout << "giving back a null" << std::endl;
        }
        return *sectionMap[id];
    }

    void Loader::open(const std::string& fn)
    {
        std::queue<std::string> files;
        std::vector<std::string> done;
        files.push(fn);
        std::ifstream fp;
        std::string cfn;

        while (files.size() != 0)
        {
            cfn = files.front();
            //files.pop();
            fp.open(fs::path(cfn).generic_string());
            if (!fp.is_open())
            {
                std::cout << "error opening file " << cfn << std::endl;
                return;
            }
            std::string line;
            std::vector<std::string> parts;
            std::string token;
            std::string delimiter = " ";
            while (std::getline(fp, line))
            {
                parts = strsplit(line, " ");

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
                    std::cout << "add line" << std::endl;
                    if (line == "\n") continue;
                    currentSection->addLine(line);
                    continue;
                }

                if (parts[0] == "use")
                {
                    std::cout << "use" << std::endl;
                    const std::string& use_fn = parts[1];
                    for (auto& e : done)
                    {
                        if (e == use_fn)
                        {
                            std::cout << "error: circular dep" << std::endl;
                            continue;
                        }
                    }

                    files.push(use_fn);
                }
            }
            done.push_back(files.front());
            files.pop();
        }
    }

    std::vector<std::string> Loader::strsplit(const std::string& str, const std::string& delim)
    { 
        std::string append = "";
        std::vector<std::string> out;
        if (delim.size() < 1)
        {
            std::cout << "bad delim" << std::endl;
            return std::vector<std::string>();
        }
        for (auto& c : str)
        {
            if (c == delim[0])
            {
                out.push_back(append);
                append = "";
                continue;
            }
            if (c == '\r' || c == '\n')
            {
                continue;
            }
            append.push_back(c);
        }
        out.push_back(append);

        return out;
    }

    size_t Loader::numSections()
    {
        return sectionMap.size();
    }
}
