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
    Entry::Entry() : Entry("")
    {

    }

    Entry::Entry(const std::string& line)
    {
        processLine(line);
    }

    Entry::~Entry()
    {

    }

    void Entry::processLine(const std::string& l)
    {
        line = l;
        std::istringstream ss(l);
        std::copy(std::istream_iterator<std::string>(ss),
                std::istream_iterator<std::string>(),
                std::back_inserter(parts));
    }

    std::string Entry::getName()
    {
        return parts[0];
    }

    size_t Entry::size()
    {
        return parts.size();
    }
}