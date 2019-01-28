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

    private:
        std::vector<Entry*> entries;
    };
}
