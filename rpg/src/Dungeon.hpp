#pragma once

#include <engine.hpp>
#include <sol/sol.hpp>

class Dungeon
{
public:

	Dungeon()
	{

	}

	~Dungeon()
	{

	}

	void generate();

private:
	void placeRoom();
	bool isRoomValid();
	void fill();
	int floor[256][256];
};
