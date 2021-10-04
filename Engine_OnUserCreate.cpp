// --- Engine.cpp ---

#include "Engine.h"

#include "olcPixelGameEngine.h"
#include "Utility.h"
#include "World.h"
#include "AssetManager.h"
#include "Object.h"

#include <fstream>   // for testing purposes, delete


using namespace std;

bool Engine::OnUserCreate() {
	std::cout << "started\n";
	f.init();
	f.newLevel();
	f.loadLevel(1);
	f.saveLevelAs("In the Brig");
	f.loadLevel(1);
	f.changeCell(Vec3Di{0,0,0}, false, 2,2,2,2,2);
	f.saveLevel();
	f.loadLevel(2);
	f.moveLevelToMap(f.currentLevel, 2);
	f.loadLevel(1);
	f.removeLevelFromMap(1);
	f.saveLevelAs("Strawberry Banana");
	f.createRotationAndAddToLevel(Vec3Df{0,0,0},Vec3Df{5,5,5},1,23);
	string pathRotation = "./Files/rotation_2_.txt";
	ofstream fout;
	fout.open(pathRotation);
	fout << "5.467 8.972";
	fout.close();
	f.saveLevel();
	f.loadLevel(1);
	for(auto it=f.allRotations.begin(); it!=f.allRotations.end(); it++) {
		if((*it)->id == 2) {
			f.moveRotationToLevel(*it, Vec3Df{0,1,2},Vec3Df{7,7,7},55,99);
		}
	}
	f.saveLevel();
	f.loadLevel(3);
	f.removeRotationFromLevel(2);
	f.saveLevel();
	for(auto it=f.allRotations.begin(); it!=f.allRotations.end(); it++) {
		if((*it)->id == 2) {
			f.deleteRotationFromAllRotations(*it);
		}
	}
	for(auto it=f.currentLevel->levelObjects.begin(); it!=f.currentLevel->levelObjects.end(); it++) {
		f.removeObjectFromLevel(*it);
		break;
	}
	f.saveLevel();
	f.loadLevel(1);
	f.addObjectToLevel("door", Vec3Df{11,12,13}, true, Vec3Df{20,21,22});
	f.saveLevel();
	f.newLevel();
	f.saveLevelAs("Jerry Giraffe");
	f.loadLevel(3);
	f.changeLevelSize(4,4,4);
	f.saveLevel();
	f.changeCell(Vec3Di{3,3,3}, true, 5,5,5,5,5);
	f.saveLevel();
	f.changeLevelSize(1,1,1);
	f.saveLevel();
	f.world.destroy();
	std::cout << "finished\n";

	// f.changeLevelSize(4,4,4);
	// f.saveLevel();
	// f.deleteLevelFromAllLevels(2);



	
	return true;
}

