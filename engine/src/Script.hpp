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

        // static methods
        static void init();
        static void regfunc(lua_CFunction, const std::string&);
        static void destroy();

        int load(const std::string&);

    private:
        void error(lua_State*, const char*, ...);
        static lua_State* L;
    };
}