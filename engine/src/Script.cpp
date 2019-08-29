#include "Script.hpp"
#include <iostream>
#include <cstdarg>
#include <cstdlib>
#include <cstdio>

namespace engine
{
    lua_State* Script::L = nullptr;

    Script::Script()
    {
        
    }

    Script::~Script()
    {

    }

    void Script::init()
    {
        L = luaL_newstate();
        luaL_openlibs(L);
    }

    void Script::regfunc(lua_CFunction func, const std::string& name)
    {
        lua_pushcfunction(L, func);
        lua_setglobal(L, name.c_str());

    }

    void Script::destroy()
    {
        if (L != nullptr)
        {
            lua_close(L);
        }
    }

    void Script::error(lua_State* L, const char* fmt, ...)
    {
        va_list argp;
        va_start(argp, fmt);
        vfprintf(stderr, fmt, argp);
        va_end(argp);
        lua_close(L);
        L = nullptr;
    }

    int Script::load(const std::string& fn)
    {
        if (luaL_loadfile(L, fn.c_str()) || lua_pcall(L, 0, 0, 0))
        {
            error(L, "cannot run lua file %s\n", lua_tostring(L, -1));
            return 1;
        }
        return 0;
    }
}
