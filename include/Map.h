#pragma once
#include <vector>
#include <stdlib.h>
#include <time.h>

typedef unsigned char MapTileChar;
typedef std::vector<std::vector<MapTileChar>> Map2D;

static std::vector<MapTileChar> MapTileChars = { static_cast<MapTileChar>(200), static_cast<MapTileChar>(201),
				static_cast<MapTileChar>(202), static_cast<MapTileChar>(203), static_cast<MapTileChar>(204)};


enum MapTileID : int {
	EMPTY = 0,
	WALL,
	SCORE,
	BOOST,
	UNKNOWNTILE
};

const static char getTileChar(MapTileID tile) {
	return MapTileChars[tile];
}

class Map
{
private:
	int MapWidth;
	int MapHeight;

	std::vector<std::vector<MapTileChar>> MapTiles{ MapHeight };

	void CreateTiles();
	bool CheckTileExistance(const size_t tileX, const size_t tileY);
	void CreateWalls();

public:

	static const int DefMapWidth = 12;
	static const int DefMapHeight = 20;

	Map(int  mapHeight = DefMapHeight, int mapWidth = DefMapWidth);

	const MapTileChar getTile(const size_t tileX, const size_t tileY);
	void setTile(const size_t tileX, const size_t tileY, const MapTileChar newTileChar);
	const std::vector<std::vector<MapTileChar>> getMap() const;
	size_t getMaxHeight();
	size_t getMaxWidth();
	void UpdateMap();
	std::vector<std::vector<int>> getRandomEmptyTile();

};

