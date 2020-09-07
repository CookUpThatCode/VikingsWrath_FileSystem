// --- Engine.cpp ---

#include "Engine.h"

#include "olcPixelGameEngine.h"
#include "Utility.h"
#include "World.h"
#include "Assets.h"
#include "Object.h"

using namespace std;

void Engine::loadAssets() {
	walls.load("./Sprites/wall_door/png");
	roofFloor.load("./Sprites/roof_floor.png");
	character.load("./Sprites/enDemon/demAttack.png");
	testCells.load("./Sprites/test_cells.png");
	newTiles.load("./Sprites/newTiles.png");
}

void Engine::saveLevel()
{
	//fout.open(level->level);

	ofstream fout("level.txt");
	fout << world.size.x << " " << world.size.y << " " << world.size.z << " ";
	for (int x = 0; x < world.size.x; x++)
		for (int y = 0; y < world.size.y; y++)
			for (int z = 0; z < world.size.z; z++)
				fout << (world.cells[x][y][z].placed ? 1 : 0) << " ";
	fout.close();
}

void Engine::loadLevel()
{
	int buffer;
	ifstream fin("level.txt");
	fin >> world.size.x; fin >> world.size.y; fin >> world.size.z;
	for (int x = 0; x < world.size.x; x++)
		for (int y = 0; y < world.size.y; y++)
			for (int z = 0; z < world.size.z; z++)
			{
				fin >> buffer;
				if (buffer == 1) world.cells[x][y][z].placed = true;
				else world.cells[x][y][z].placed = false;
			}
	fin.close();
}



