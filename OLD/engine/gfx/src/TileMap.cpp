#include "TileMap.hpp"
#include <cstdlib>
#include <nlohmann/json.hpp>
#include <experimental/filesystem>
#include <iostream>
#include <cstring>
#include "Assets.hpp"
#include "Texture.hpp"
#include "Util.hpp"

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
			map_p[i] = (TILE*)malloc(c * sizeof(TILE));
		}
	}

	void TileMap::loadMap(const std::string& fn)
	{
		// open json file
		json o = Util::loadJson(fn);

		// build tilemap
		initMap(o["rows"], o["cols"], o["tilesize"]);

		int r = 0;
		int c = 0;

		for (auto& e : o["tiles"])
		{
			r = e[0].get<int>();
			c = e[1].get<int>();

			map_p[r][c].solid = e[3].get<int>();
			int tex = e[2].get<int>();
			strcpy(map_p[r][c].texture, o["subtextures"][tex]["fn"].get<std::string>().c_str());
		}
	}

	void TileMap::draw(Context& ctx)
	{
		Texture* tex = nullptr;
		int r = 0;
		int c = 0;

		for (r=0; r<rows; r++)
		{
			for (c=0; c<cols; c++)
			{
				TILE* tile = &map_p[r][c];
				tex = Assets::getTexture(std::string(tile->texture));
				SDL_Rect rect;
				rect.x = r * gridSize;
				rect.y = c * gridSize;
				rect.w = gridSize;
				rect.h = gridSize;
				SDL_RenderCopy(ctx.getRenderer(), tex->use(), nullptr, &rect);
			}
		}
	}
}