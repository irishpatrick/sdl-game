#include <vector>
#include <iostream>
#include <iostream>

namespace stf 
{
    template <typename T>
    T Section::getValue(const std::string& name)
    {
        for (auto& e : entries)
        {
            if (e->getName() == name)
            {
                return e->getPart<T>(1);
            }
        }
    }

    template <typename T>
    T Section::getValue(int index, int pos)
    {
        return entries[index]->getPart<T>(pos);
    }

    template <typename T>
    std::vector<T> Section::getVector(const std::string& name)
    {
        std::vector<T> out;
        for (auto& e : entries)
        {
            if (e->getName() == name)
            {
                int i;
                for (i=1; i<e->size(); i++)
                {
                    out.push_back(e->getPart<T>(name));
                }
            }
        }

        return out;
    }

    template <typename T>
    std::vector<T> Section::getLines()
    {
        std::vector<T> out;
        for (auto& e : entries)
        {
            out.push_back(e->getLine<T>());   
        }
    }
}