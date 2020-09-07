#include "FileSystem.h"

#include <iostream>
#include <fstream>

using std::string;

#include "Level.h"


void FileSystem::init() {
    pathAllRotationsBank = "allRotationsBank.txt";
    pathAllLevelsBank = "allLevelsBank.txt";

    fin.open(pathAllRotationsBank);
    int id;
    while (fin >> id) {
        allRotations.push_back(id);
    }
    fin.close();

    fin.open(pathAllLevelsBank);
    int mapLevelNumber;
    string name;
    Level* level;
    while (fin >> id) {
        fin >> mapLevelNumber;
        fin >> name;
        level = new Level(this, id, mapLevelNumber, name);
        allLevels.push_back(level);
    }
    fin.close();
}

void FileSystem::addObjectToLevel(string name) {    
    if (name == "player") {
        Player* player = new Player(name, &(a.pAttack), &(a.pClimb), &(a.pDash), &(a.pDeath), &(a.pHurt), &(a.pIdle), &(a.pJump), 
                &(a.pRun), &(a.pAttackRun), &(a.pSkid), &(a.pWalk), &(a.pAttackWalk), &(a.directionIndicator));
        currentLevel->levelCharacters.push_back(player);
    }
    else if (name == "rotation") {
        Rotation* rotation = new Rotation(name, getNextRotationID(), &(a.rotation));
        currentLevel->levelRotations.push_back(rotation);
    }
    else if (name == "axe") {
        Axe* axe = new Axe(f, name);
        f->currentLevel->levelObjects.push_back(axe);
    }

}
