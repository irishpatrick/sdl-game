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

        void addValue(const std::string&);
        template <class T>
        T getValue(const std::string&);

        template <class T>
        std::vector<T> getValues(int);

        void addLine(const std::string&);
        Entry* getLine(int);

        template <class T>
        Entry* getLineByVal(const T&);

        size_t getSize();

    private:
        std::vector<Entry*> entries;
        std::string id;
    };
}

#include "Section.inl"
