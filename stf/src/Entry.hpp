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

    private:
        std::vector<std::string> parts;
    };
}