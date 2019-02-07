#include <boost/lexical_cast.hpp>
#include <iostream>

namespace stf
{   
    template <typename T>
    T Entry::getPart(int index)
    {
        return boost::lexical_cast<T>(parts[index]);
    }

    template <typename T>
    T Entry::getLine()
    {
        return boost::lexical_cast<T>(line);
    }
}