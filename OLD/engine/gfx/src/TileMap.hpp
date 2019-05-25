#pragma once

#include "core.hpp"
#include "extra.hpp"
#include <string>
#include <fstream>
#include <map>

namespace engine
{
	typedef struct _TILE
	{
		char texture[100];
		int solid;
	} TILE;

	class TileMap : public Sprite
	{
	public:
		TileMap();
		~TileMap();

		void initMap(int, int, int);
		void loadMap(const std::string&);
		void draw(Context&);

	private:
		int gridSize;
		int rows;
		int cols;
		TILE** map_p;
		BoundingBox** solids_p;
	};
}
