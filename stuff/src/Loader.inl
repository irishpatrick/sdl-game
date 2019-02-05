#include <string>
#include <boost/lexical_cast.hpp>
#include <iostream>

namespace stf
{
    template <class T>
    T Loader::getField(const std::string& name)
    {
        return boost::lexical_cast<T>(fieldMap[name]);
    }
}