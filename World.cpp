// --- World.cpp ---

#include "World.h"

#include "olcPixelGameEngine.h"
#include "Utility.h"


using namespace std;

World::~World()
{
	for (int x = 0; x < size.x; x++)
	{
		for (int y = 0; y < size.y; y++)
		{
			free(cells[x][y]);
		}
		free(cells[x]);
	}
	free(cells);
}

void World::Create(int width, int height, int depth)
{
	size = { width, height, depth };
	cells = (Cell***)malloc(width * sizeof(Cell**));    // dynamically allocate in 3 dimensions
	for (int x = 0; x < width; x++)
	{
		cells[x] = (Cell**)malloc(height * sizeof(Cell*));
		for (int y = 0; y < height; y++)
		{
			cells[x][y] = (Cell*)malloc(depth * sizeof(Cell));
		}
	}
	// initialize to all placed for development
	for (int x = 0; x < size.x; x++)
		for (int y = 0; y < size.y; y++)
			for (int z = 0; z < size.z; z++)
				cells[x][y][z].placed = true;
}

Cell& World::getCell(const Vec3Di& location)
{
	if (location.x >= 0 && location.x < size.x &&
		location.y >= 0 && location.y < size.y &&
		location.z >= 0 && location.z < size.z)
		return cells[location.x][location.y][location.z];
	else
		return nullCell;
}
