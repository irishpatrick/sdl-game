

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
}