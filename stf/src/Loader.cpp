#include "Loader.hpp"
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::experimental::filesystem;

namespace stf
{
    Loader::Loader()
    {

    }

    Loader::~Loader()
    {

    }

    void Loader::open(const std::string& fn)
    {
        std::ifstream fp;
        fp.open(fs::path(fn).generic_string());
        std::string line;
        std::vector<std::string> parts;
        while (std::getline(fp, line))
        {

        }
    }
}
