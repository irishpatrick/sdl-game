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

        template <class T>
        T getValue(int);

    private:
        std::vector<std::string> parts;
    };
}