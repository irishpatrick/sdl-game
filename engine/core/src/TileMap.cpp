#include "TileMap.hpp"
#include <cstdlib>
#include <nlohmann/json.hpp>
#include <experimental/filesystem>
#include <iostream>

namespace fs = std::experimental::filesystem;
using json = nlohmann::json;

namespace engine
{
	TileMap::TileMap() : Sprite()
	{
		rows = 0;
		cols = 0;
		gridSize = 0;
		map_p = nullptr;
		solids_p = nullptr;
	}

	TileMap::~TileMap()
	{
		// dealloc map_p if needed
		if (map_p != nullptr)
		{
			for (int i = 0; i < rows; i++)
			{
				free(map_p[i]);
			}
			free(map_p);
		}

		if (solids_p != nullptr)
		{
			for (int i = 0; i < rows*cols; i++)
			{
				delete solids_p[i];
			}
			free(solids_p);
		}
	}

	void TileMap::initMap(int r, int c, int s)
	{
		rows = r;
		cols = c;
		gridSize = s;

		// allocate rows
		map_p = (TILE**)malloc(r * sizeof(TILE*));
		
		// allocate cols
		for (int i = 0; i < r; i++)
		{
			map_p[i] = (TILE*)malloc(r * sizeof(TILE));
		}
	}

	void TileMap::loadMap(const std::string& fn)
	{
		// open json file
		fs::path fp(fn);
		std::ifstream in(fp.generic_string());
		if (in.fail())
		{
			std::cout << "cannot open " << fn << std::endl;
			return;
		}
		json o;

		// parse json file
		try
		{
			o << in;
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}

		// build tilemap
		initMap(o["rows"], o["cols"], o["tileSize"]);

		int r = 0;
		int c = 0;

		for (auto& e : o["tiles"])
		{
			map_p[r][c].solid = e["solid"];
			map_p[r][c].solid = e["texture"];
			
			r++;
			if (r == rows)
			{
				r = 0;
				c++;
			}
		}
	}
}