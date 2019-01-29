#include "Section.hpp"

namespace stf
{
    Section::Section()
    {

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
        //entries.push_back()
    }
}
