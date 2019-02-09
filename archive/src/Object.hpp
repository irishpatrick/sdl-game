#pragma once

#include "core_api.hpp"

namespace engine
{

    class Object
	{
    public:
        CORE_API Object();
        CORE_API ~Object();

        float x;
        float y;
        bool dynamic;
    };

}