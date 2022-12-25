#include "Level.h"
#include <cmath>

int Level::IsWall(int x, int y)
{
	int x_cell = (int)(x / tile_size);
	int y_cell = (int)(y / tile_size);
	if (0 <= x_cell && x_cell < map_colomns &&
		0 <= y_cell && y_cell < map_raw)
	{
		return level[y_cell][x_cell];
	}

	// Any thing outsize the map is a wall 
	return true;
}

float Level::GetYCellBorder(float y)
{
	return floor(y / tile_size) * tile_size;
}

float Level::GetXCellBorder(float x)
{
	return floor(x / tile_size) * tile_size;
}

float Level::GetTileSize()
{
	return tile_size;
}
