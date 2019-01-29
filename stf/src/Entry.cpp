#include "Entry.hpp"
#include <iostream>
#include <stdexcept>
#include <boost/lexical_cast.hpp>

namespace stf
{
    Entry::Entry()
    {

    }

    Entry::~Entry()
    {

    }

    template <class T>
    T Entry::getValue(int pos)
    {
        if (pos >= parts.size())
        {
            throw std::invalid_argument("pos is out of range");
        }

        try
        {
            return boost::lexical_cast<T>(parts[pos]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}