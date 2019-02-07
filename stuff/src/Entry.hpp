#pragma once

#include <vector>
#include <string>
#include <cstdint>

namespace stf
{

    class Entry
    {
    public:
        Entry();
        Entry(const std::string&);
        ~Entry();

        void processLine(const std::string&);

        std::string getName();

        template <typename T>
        T getPart(int);

        template <typename T>
        T getLine();

        size_t size();
    
    private:
        std::string line;
        std::vector<std::string> parts;
    };
}

#include "Entry.inl"