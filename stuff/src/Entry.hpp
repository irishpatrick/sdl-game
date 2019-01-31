#pragma once

#include <vector>
#include <string>

namespace stf
{
    class Entry
    {
    public:
        Entry();
        ~Entry();

        void setLine(const std::string&);

        template <class T>
        T getValue(unsigned int);

        template <class T>
        std::vector<T> toVector();

    private:
        std::vector<std::string> parts;
    };
}

#include "Entry.inl"