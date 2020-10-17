// --- Engine.cpp ---

#include "Engine.h"

#include "olcPixelGameEngine.h"
#include "Utility.h"
#include "World.h"
#include "AssetManager.h"
#include "Object.h"

using namespace std;

bool Engine::OnUserCreate()
{
	f.init();
	f.newLevel();
	f.loadLevel(1);
	// f.saveLevelAs("In the Brig");
	f.newLevel();
	
	return true;
}

