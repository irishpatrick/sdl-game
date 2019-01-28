#pragma once

#include <engine.hpp>

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