#include "Map.h"

void Map::CreateTiles() {
	MapTiles.clear();
	for (size_t mapHeight = 0; mapHeight < MapHeight; mapHeight++) {
		std::vector<MapTileChar> newTile(MapWidth, MapTileChars[MapTileID::EMPTY]);
		MapTiles.push_back(newTile);
	}
}

bool Map::CheckTileExistance(const size_t tileX, const size_t tileY)
{
	if (tileX >= MapWidth || tileX < 0) {
		return false;
	}
	if (tileY >= MapHeight || tileY < 0) {
		return false;
	}

	return true;
}

void Map::CreateWalls() {
	//Üst duvar
	for (size_t mapWidth = 0; mapWidth < MapWidth; mapWidth++) {
		MapTiles[0][mapWidth] = MapTileChars[MapTileID::WALL];
	}

	//Alt duvar 
	for (size_t mapWidth = 0; mapWidth < MapWidth; mapWidth++) {
		MapTiles[MapHeight - 1][mapWidth] = MapTileChars[MapTileID::WALL];
	}

	//Orta duvar
	for (size_t mapHeight = 1; mapHeight < MapHeight - 1; mapHeight++) {
		MapTiles[mapHeight][0] = MapTileChars[MapTileID::WALL];
		MapTiles[mapHeight][MapWidth - 1] = MapTileChars[MapTileID::WALL];
	}

}

Map::Map(int mapHeight, int mapWidth)
{
	MapWidth = mapWidth;
	MapHeight = mapHeight;

	CreateTiles();
	CreateWalls();
}

const MapTileChar Map::getTile(const size_t tileX, const size_t tileY)
{
	if (!CheckTileExistance(tileX, tileY)) {
		return MapTileChars[MapTileID::UNKNOWNTILE];
	}

	return MapTiles[tileY][tileX];
}

void Map::setTile(const size_t tileX, const size_t tileY, MapTileChar newTileChar)
{
	if (tileX > MapWidth) {
		return; // Error
	}
	else if (tileY > MapHeight) {
		return; // Error
	}

	MapTiles[tileY][tileX] = newTileChar;
}

const std::vector<std::vector<MapTileChar>> Map::getMap() const
{
	return MapTiles;
}

size_t Map::getMaxHeight()
{
	return MapHeight;
}

size_t Map::getMaxWidth()
{
	return MapWidth;
}

void Map::UpdateMap() {
	CreateTiles();
	CreateWalls();

}

std::vector<std::vector<int>> Map::getRandomEmptyTile()
{
	return std::vector<std::vector<int>>();
}
