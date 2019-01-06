#pragma once

#include <engine.hpp>
#include "Fighter.hpp"

class Team : public engine::Group
{
public:
    Team();
    ~Team();

private:
	Fighter fighters[5];
};
