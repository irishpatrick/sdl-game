#include "Section.hpp"

namespace stf
{
    Section::Section()
    {
        id = "";
    }

    Section::Section(const std::string& str)
    {
        id = str;
    }

    Section::~Section()
    {
        for (auto& e : entries)
        {
            if (e != nullptr)
            {
                delete e;
            }
        }
    }

    void Section::addLine(const std::string& line)
    {
        Entry* e = new Entry();
        e->setLine(line);
        entries.push_back(e);
    }

    Entry& Section::getline(int pos)
    {
        return *entries[pos];
    }
}
