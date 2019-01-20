#pragma once

#include "Sprite.hpp"
#include <string>
#include <fstream>

namespace engine
{
	typedef struct _TILE
	{
		int texture;
		bool solid;
	} TILE;

	class TileMap : public Sprite
	{
	public:
		TileMap();
		TileMap();

		void initMap(int, int, int);
		void loadMap(const std::string&);

	private:
		int gridSize;
		int rows;
		int cols;
		TILE** map_p;
	};
};