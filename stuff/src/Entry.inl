#include <boost/lexical_cast.hpp>
#include <iostream>

namespace stf
{   
    template <typename T>
    T Entry::getPart(int index)
    {
        return boost::lexical_cast<T>(parts[index]);
    }
}