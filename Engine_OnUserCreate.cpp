// --- Engine.cpp ---

#include "Engine.h"

#include "olcPixelGameEngine.h"
#include "Utility.h"
#include "World.h"
#include "Assets.h"
#include "Object.h"

using namespace std;

bool Engine::OnUserCreate()
{
	a.load(this);
	f.init(this);


	testout.open("testout.txt");
	testout << "This is from OnUserCreate\n";
	// Player testplayer(this);

	angleOut.open("angle.txt");
	angleIn.open("angle.txt");

	loadAssets();

	world.Create(10, 5, 3);
	loadLevel();

	for (int x = 0; x < world.size.x; x++)
		for (int y = 0; y < world.size.y; y++)
			for (int z = 0; z < world.size.z; z++)
			{
				Cell& testCell = world.getCell({ x,y,z });
				//testCell.placed=true;
				testCell.tiles[Top] = { ((x + y + z) % 3) * floorDims.x,0 };
				testCell.tiles[East] = { ((x + y + z) % 3) * wallDims.x,floorDims.y };
				testCell.tiles[North] = { ((x + y + z) % 3) * wallDims.x,floorDims.y };
				testCell.tiles[West] = { ((x + y + z) % 3) * wallDims.x,floorDims.y };
				testCell.tiles[South] = { ((x + y + z) % 3) * wallDims.x,floorDims.y };
			}



	return true;
}

