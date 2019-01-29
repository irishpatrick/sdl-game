#include "Entry.hpp"
#include <iostream>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <string>

namespace stf
{
    Entry::Entry()
    {

    }

    Entry::~Entry()
    {

    }

    void Entry::setLine(const std::string& str)
    {
        std::istringstream in(str);
        parts = std::vector<std::string>(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>());
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