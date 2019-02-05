#include <vector>
#include <iostream>
#include <iostream>

namespace stf 
{
    template <class T>
    Entry* Section::getLineByVal(const T& val)
    {
        for (auto& e : entries)
        {
            if (e->getValue<T>(0) == val)
            {
                return e;
            }
        }
        return nullptr;
    }

    template <class T>
    std::vector<T> Section::getValues(int pos)
    {
        std::vector<T> out;
        for (auto& e : entries)
        {
            T value = e->getValue<T>(pos);
            std::cout << "value: " << value << std::endl;
            out.push_back(value);
        }

        return out;
    }
}