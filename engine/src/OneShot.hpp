#pragma once

#include "core_api.hpp"
#include <cstdio>

namespace engine
{

class OneShot
{
public:
	CORE_API OneShot();
	CORE_API ~OneShot();

	CORE_API void check(bool);
	CORE_API bool fire();
	CORE_API bool altFire();
	CORE_API void setPointer(bool*);

private:
    bool state;
    bool reset;
	bool* ptr;
};

}
