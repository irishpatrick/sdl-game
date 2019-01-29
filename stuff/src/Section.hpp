#pragma once

#include "Entry.hpp"
#include <vector>

namespace stf
{
    class Section
    {
    public:
        Section();
        ~Section();

        void addLine(const std::string&);

    private:
        std::vector<Entry*> entries;
    };
}
