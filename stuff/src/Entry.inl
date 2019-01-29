#include <boost/lexical_cast.hpp>
#include <iostream>

namespace stf
{
    template <class T>
    T Entry::getValue(unsigned int pos)
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

        return T();
    }   
}