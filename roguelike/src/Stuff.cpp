#include "Stuff.hpp"

bool json_has(json& o, const std::string& name)
{
    return o.find(name) != o.end();
}
