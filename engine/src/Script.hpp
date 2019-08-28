#pragma once

#include <string>
#include <vector>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

namespace engine
{
    class Script
    {
    public:
        Script();
        ~Script();

    private:
        lua_State* L;
    };
}