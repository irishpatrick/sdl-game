#pragma once

#include "Entry.hpp"
#include <vector>
#include <string>

namespace stf
{
    class Section
    {
    public:
        Section();
        Section(const std::string&);
        ~Section();

        void addLine(const std::string&);

        Entry& getline(int);

    private:
        std::vector<Entry*> entries;
        std::string id;
    };
}
