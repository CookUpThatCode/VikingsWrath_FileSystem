// --- World.cpp ---

#include "World.h"

#include <fstream>
#include <iostream>

#include "olcPixelGameEngine.h"
#include "Utility.h"

using std::string;
using std::ifstream;
using std::ofstream;

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

void World::create(const string& pathLevelCells, int width, int height, int depth)
{
	size = {width, height, depth};

	cells = (Cell***)malloc(width * sizeof(Cell**));   
	for (int x = 0; x < width; x++)
	{
		cells[x] = (Cell**)malloc(height * sizeof(Cell*));
		for (int y = 0; y < height; y++)
		{
			cells[x][y] = (Cell*)malloc(depth * sizeof(Cell));
		}
	}

	ifstream fin;
	int buffer;
	fin.open(pathLevelCells);
	if (!fin) {
		std::cout << "Couldn't open 'pathLevelCells' [in World::create()]\n";
	}
	else {
		fin >> buffer;
		fin >> buffer;
		fin >> buffer;
		for (int x = 0; x < size.x; x++) {
			for (int y = 0; y < size.y; y++) {
				for (int z = 0; z < size.z; z++) {
					fin >> buffer;
					cells[x][y][z].placed = buffer;
					fin >> buffer;
					cells[x][y][z].tiles[EAST] = buffer;
					fin >> buffer;
					cells[x][y][z].tiles[NORTH] = buffer;
					fin >> buffer;
					cells[x][y][z].tiles[WEST] = buffer;
					fin >> buffer;
					cells[x][y][z].tiles[SOUTH] = buffer;
					fin >> buffer;
					cells[x][y][z].tiles[TOP] = buffer;
				}
			}
		}
		fin.close();
	}
}

void World::save(const string& pathLevelCells) {
	ofstream fout;
	fout.open(pathLevelCells);
	if (!fout) {
		std::cout << "Couldn't open 'pathLevelCells' [in World::save()]\n";
	}
	else {
		fout << " " << size.x << " " << size.y << " " << size.z << " ";
		for (int x = 0; x < size.x; x++) {
			for (int y = 0; y < size.y; y++) {
				for (int z = 0; z < size.z; z++) {
					fout << (cells[x][y][z].placed ? 1 : 0) << " ";
					fout << cells[x][y][z].tiles[EAST] << " ";
					fout << cells[x][y][z].tiles[NORTH] << " ";
					fout << cells[x][y][z].tiles[WEST] << " ";
					fout << cells[x][y][z].tiles[SOUTH] << " ";
					fout << cells[x][y][z].tiles[TOP];
				}
			}
		}
		fout.close();
	}
}

void World::resize(int width, int height, int depth) {
	World newWorld;
	newWorld.size = {width, height, depth};

	newWorld.cells = (Cell***)malloc(width * sizeof(Cell**));   
	for (int x = 0; x < width; x++)
	{
		newWorld.cells[x] = (Cell**)malloc(height * sizeof(Cell*));
		for (int y = 0; y < height; y++)
		{
			newWorld.cells[x][y] = (Cell*)malloc(depth * sizeof(Cell));
		}
	}

	for (int x = 0; x < size.x && x < newWorld.size.x; x++) {
		for (int y = 0; y < size.y && y < newWorld.size.y; y++) {
			for (int z = 0; z < size.z && z < newWorld.size.z; z++) {
				newWorld.cells[x][y][z].placed = cells[x][y][z].placed;
				newWorld.cells[x][y][z].tiles[EAST] = cells[x][y][z].tiles[EAST];
				newWorld.cells[x][y][z].tiles[NORTH] = cells[x][y][z].tiles[NORTH];
				newWorld.cells[x][y][z].tiles[WEST] = cells[x][y][z].tiles[WEST];
				newWorld.cells[x][y][z].tiles[SOUTH] = cells[x][y][z].tiles[SOUTH];
				newWorld.cells[x][y][z].tiles[TOP] = cells[x][y][z].tiles[TOP];
			}
		}
	}
	newWorld.nullCell = nullCell;
	*this = World(newWorld);
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
