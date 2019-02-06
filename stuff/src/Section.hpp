#pragma once

#include "Entry.hpp"
#include <vector>
#include <string>
#include <cstdlib>
#include <iterator>

namespace stf
{
    class Section
    {
    public:
        Section();
        Section(const std::string&);
        ~Section();

        template <typename T>
        T getValue(const std::string&);

        template <typename T>
        T getValue(int, int);

        template <typename T>
        std::vector<T> getVector(const std::string&);

        template <typename T>
        std::vector<T> getVector(int);

        void addLine(const std::string&);

    private:
        std::vector<Entry*> entries;
        std::string id;
    };
}

#include "Section.inl"
