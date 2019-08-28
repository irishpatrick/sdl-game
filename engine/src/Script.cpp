#include "Script.hpp"
#include <iostream>

namespace engine
{
    Script::Script() :
        L(nullptr)
    {
        L = luaL_newstate();
        luaL_openlibs(L);
    }

    Script::~Script()
    {
        if (L != nullptr)
        {
            lua_close(L);
        }
    }
}
