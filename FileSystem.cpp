#include "FileSystem.h"

#include <iostream>
#include <fstream>
#include <stdio.h>

using std::string;
using std::list;
using std::stoi;
using std::ifstream;
using std::ofstream;

#include "Level.h"


FileSystem::~FileSystem() {
    delete defaultLevel;
    delete currentLevel;
    for (list<Level*>::iterator it=allLevels.begin(); it != allLevels.end(); ++it) {
        delete *it;
    }
    for (list<Object*>::iterator it=menuObjectButtons.begin(); it != menuObjectButtons.end(); ++it) {
        delete *it;
    }
    for (list<Object*>::iterator it=menuCharacterButtons.begin(); it != menuCharacterButtons.end(); ++it) {
        delete *it;
    }
    for (list<Object*>::iterator it=menuRotationButtons.begin(); it != menuRotationButtons.end(); ++it) {
        delete *it;
    }
    for (list<Object*>::iterator it=menuLevelButtons.begin(); it != menuLevelButtons.end(); ++it) {
        delete *it;
    }
    for (list<Object*>::iterator it=menuOptionButtons.begin(); it != menuOptionButtons.end(); ++it) {
        delete *it;
    }
    for (list<Object*>::iterator it=menuTileButtons.begin(); it != menuTileButtons.end(); ++it) {
        delete *it;
    }
    for (list<Object*>::iterator it=menuBlockButtons.begin(); it != menuBlockButtons.end(); ++it) {
        delete *it;
    }
}

void FileSystem::init() {
    currentLevel = nullptr;
    mapLevels = {nullptr, nullptr, nullptr, nullptr, nullptr};
    a.init(menuRotationButtons, menuLevelButtons, menuOptionButtons, menuTileButtons, menuBlockButtons, 
            menuCharacterButtons, menuObjectButtons);
    world.size = {0,0,0};

    pathAllRotationsBank = "./Files/allRotationsBank.txt";
    pathAllLevelsBank = "./Files/allLevelsBank.txt";

    defaultLevel = new Level(-1, -1, "Default");

    ifstream fin;
    fin.open(pathAllRotationsBank);
    if (!fin) {
        std::cout << "Couldn't open 'pathAllRotationsBank' [in FileSystem::init()]\n";
    }
    else {
        int id;
        while (fin >> id) {
            allRotations.push_back(id);
        }
        fin.close();
    }
    

    fin.open(pathAllLevelsBank);
    if (!fin) {
        std::cout << "Couldn't open 'pathAllLevelsBank' [in FileSystem::init()]\n";
    }
    else {
        int mapLevelNumber;
        int id;
        string name;
        Level* level;
        while (fin >> id) {
            fin >> mapLevelNumber;
            fin.ignore();
            std::getline(fin, name, '*');
            level = new Level(id, mapLevelNumber, name);
            allLevels.push_back(level);
        }
        fin.close();
    }
    
    int num;
    for(list<Level*>::iterator it=allLevels.begin(); it != allLevels.end(); ++it) {
        num = (*it)->mapLevelNumber;
        if (num != -1) {
            mapLevels[num-1] = *it;
        }
    }
}

void FileSystem::loadLevel(int id_) {
    if (id_ != -1) {    // if not default level
        for (list<Level*>::iterator it=allLevels.begin(); it != allLevels.end(); ++it) {
            if ((*it)->id == id_) {
                (*it)->load(currentLevel, world, a);
                break;
            }
        }
    }
    else {
        defaultLevel->load(currentLevel, world, a);
    }
    
}

void FileSystem::saveLevel() {
    currentLevel->save(world);
}

void FileSystem::saveLevelAs(string name) {
    int id = getNextLevelID();
    currentLevel->saveAs(world, currentLevel, id, name);
    allLevels.push_back(currentLevel);
    writeAllLevelsToFile();
}

void FileSystem::removeLevelFromMap(int mapLevelNumber) {
    mapLevels[mapLevelNumber]->mapLevelNumber = -1;
    writeAllLevelsToFile();
}

void FileSystem::moveLevelToMap(Level* level, int mapLevelNumber_) {
    level->mapLevelNumber = mapLevelNumber_;
    mapLevels[mapLevelNumber_] = level;
    writeAllLevelsToFile();
}

void FileSystem::deleteLevelFromAllLevels(int id_) {  
    if (currentLevel && currentLevel->id == id_) {
        currentLevel->~Level();
    }
    for (int i=0; i<5; ++i) {
        if (mapLevels[i]->id == id_) {
            mapLevels[i] = nullptr;
        }
    }
    for (list<Level*>::iterator it=allLevels.begin(); it != allLevels.end(); ++it) {
        if ((*it)->id == id_) {
            string pathLevelCells = (*it)->pathLevelCells;
            string pathLevelObjects = (*it)->pathLevelObjects;
            string pathLevelRotations = (*it)->pathLevelRotations;
            string pathLevelCharacters = (*it)->pathLevelCharacters;
            remove(pathLevelCells.c_str());
            remove(pathLevelObjects.c_str());
            remove(pathLevelRotations.c_str());
            remove(pathLevelCharacters.c_str());
            delete *it;
            allLevels.erase(it);
        }
    }
    writeAllLevelsToFile();
}

void FileSystem::writeAllLevelsToFile() {
    ofstream fout;
    fout.open(pathAllLevelsBank);
    if (!fout) {
        std::cout << "Couldn't open 'pathAllLevelsBank' [in FileSystem::writeAllLevelsToFile()]\n";
    }
    else {
        for (list<Level*>::iterator it=allLevels.begin(); it != allLevels.end(); ++it) {
            fout << " " << (*it)->id << " " << (*it)->mapLevelNumber << " " << (*it)->name << "*";
        }
        fout.close();
    }
}

void FileSystem::writeAllRotationsToFile() {
    ofstream fout;
    fout.open(pathAllRotationsBank);
    if (!fout) {
        std::cout << "Couldn't open 'pathAllRotationsBank' [in FileSystem::writeAllRotationsToFile()]\n";
    }
    else {
        for (list<int>::iterator it=allRotations.begin(); it != allRotations.end(); ++it) {
            fout << " " << (*it);
        }
        fout.close();
    }
}

void FileSystem::removeRotationFromLevel(int id_) {   
    for (list<Rotation*>::iterator it=currentLevel->levelRotations.begin(); it != currentLevel->levelRotations.end(); ++it) {
        if ((*it)->getID() == id_) {
            currentLevel->levelRotations.erase(it);
        }
    }
}

void FileSystem::moveRotationToLevel(int id_, Vec3Df positionPlaced, Vec3Df linkedTo, int yRangeMin, int yRangeMax) {
    Rotation* rotation = new Rotation("rotation", id_, &(a.rotation), positionPlaced, linkedTo, yRangeMin, yRangeMax);
    currentLevel->levelRotations.push_back(rotation);
}

void FileSystem::deleteRotationFromAllRotations(int id_) {  // this option only available if a level is loaded.
            // otherwise you can't access list of levelRotations from current level, and can't write to levelRotations file
    for (list<Rotation*>::iterator it=currentLevel->levelRotations.begin(); it != currentLevel->levelRotations.end(); ++it) {
        if ((*it)->getID() == id_) {
            removeRotationFromLevel(id_);
        }
    }
    for (list<int>::iterator it=allRotations.begin(); it != allRotations.end(); ++it) {
        if ((*it) == id_) {
            allRotations.erase(it);
        }
    }
    writeAllRotationsToFile();
    string pathRotation = "./Files/rotation_" + std::to_string(id_) + "_.txt";
    remove(pathRotation.c_str());
}

void FileSystem::createRotationAndAddToLevel(Vec3Df positionPlaced, Vec3Df linkedTo, int yRangeMin, int yRangeMax) {
    int id = getNextRotationID();
    Rotation* rotation = new Rotation("rotation", id, &(a.rotation), positionPlaced, linkedTo, yRangeMin, yRangeMax);
    currentLevel->levelRotations.push_back(rotation);
    allRotations.push_back(rotation->getID());
    writeAllRotationsToFile();
}

void FileSystem::addObjectToLevel(string name, Vec3Df positionPlaced, bool isLinked, Vec3Df linkedTo) {  // linked to will be "null" by default
                                                    // passed in by engine as {-1, -1, -1}. have a "null" Vec3Df in engine to pass in
    if (name == "axeButton") {
        Axe* axe = new Axe(name, &(a.axe), positionPlaced);
        currentLevel->levelObjects.push_back(axe);
    }
    else if (name == "doorButton") {
        Door* door = new Door(name, &(a.door), positionPlaced, isLinked, linkedTo);
        currentLevel->levelObjects.push_back(door);
    }
    else if (name == "playerButton") {    // add a catch. only one player allowed. this will be from the engine's side
        Player* player = new Player("player", &(a.pAttack), &(a.pClimb), &(a.pDash), &(a.pDeath), &(a.pHurt), &(a.pIdle), 
                &(a.pJump), &(a.pRun), &(a.pAttackRun), &(a.pSkid), &(a.pWalk), &(a.pAttackWalk), &(a.directionIndicator),
                positionPlaced);
        currentLevel->levelCharacters.push_front(player);
    }
}

void FileSystem::removeObjectFromLevel(Object* object) {
    if (object->name == "rotation") {
        for (list<Rotation*>::iterator it=currentLevel->levelRotations.begin(); it != currentLevel->levelRotations.end(); ++it) {
            if (object == (*it)) {
                currentLevel->levelRotations.erase(it);
            }
        }
    }
    else if (object->name == "player" || object->name == "enDragon" || object->name == "enMedusa" || object->name == "enDemon" 
            || object->name == "guide") {
        for (list<Character*>::iterator it=currentLevel->levelCharacters.begin(); it != currentLevel->levelCharacters.end(); ++it) {
            if (object == (*it)) {
                currentLevel->levelCharacters.erase(it);
            }
        }
    }
    else {   // all other objects
        for (list<Object*>::iterator it=currentLevel->levelObjects.begin(); it != currentLevel->levelObjects.end(); ++it) {
            if (object == (*it)) {
                currentLevel->levelObjects.erase(it);
            }
        }
    }
}



