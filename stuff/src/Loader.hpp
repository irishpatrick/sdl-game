#pragma once

#include <map>
#include <vector>
#include "Section.hpp"
#include <cstdlib>

namespace stf
{
    class Loader
    {
    public:
        Loader();
        ~Loader();

        void open(const std::string&);
        Section* getSection(const std::string&);

        template <class T>
        T getField(const std::string&);

        size_t numSections();
        size_t numFields();

    private:
        std::vector<std::string> strsplit(const std::string&, const std::string&);

        std::map<std::string, Section*> sectionMap;
        std::map<std::string, std::string> fieldMap;
        Section* currentSection;

    };
}

#include "Loader.inl"