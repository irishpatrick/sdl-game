#pragma once

#include <map>
#include "Section.hpp"

namespace stf
{
    class Loader
    {
    public:
        Loader();
        ~Loader();

        void open(const std::string&);

        std::map<std::string, Section*> sectionMap;
        Section* currentSection;
    };
}
