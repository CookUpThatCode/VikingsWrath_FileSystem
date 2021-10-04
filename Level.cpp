#include "Level.h"
#include "Engine.h"
#include "utility.h"
#include <stdio.h>
#include <fstream>

using std::string;
using std::list;
using std::ifstream;
using std::ofstream;
using std::to_string;

Level::Level(int id, int mapLevelNumber, string name) 
    : id(id), name(name), mapLevelNumber(mapLevelNumber) {
    pathLevelCells = "./Files/level_" + to_string(id) + "_cells.txt";
    pathLevelObjects = "./Files/level_" + to_string(id) + "_objects.txt";
    pathLevelRotations = "./Files/level_" + to_string(id) + "_rotations.txt";
    pathLevelCharacters = "./Files/level_" + to_string(id) + "_characters.txt";
    playerPlaced = false;
}

Level::~Level() {
    for (list<Rotation*>::iterator it=levelRotations.begin(); it != levelRotations.end(); ++it) {
        delete *it;
    }
    levelRotations.clear();
    for (list<Object*>::iterator it=levelObjects.begin(); it != levelObjects.end(); ++it) {
        delete *it;
    }
    levelObjects.clear();
    for (list<Character*>::iterator it=levelCharacters.begin(); it != levelCharacters.end(); ++it) {
        delete *it;
    }
    levelCharacters.clear();
}

void Level::unload() {
    for (list<Rotation*>::iterator it=levelRotations.begin(); it != levelRotations.end(); ++it) {
        delete *it;
    }
    levelRotations.clear();
    for (list<Object*>::iterator it=levelObjects.begin(); it != levelObjects.end(); ++it) {
        delete *it;
    }
    levelObjects.clear();
    for (list<Character*>::iterator it=levelCharacters.begin(); it != levelCharacters.end(); ++it) {
        delete *it;
    }
    levelCharacters.clear();
}

void Level::load(Level*& currentLevel, World& world, AssetManager& a) {
    if (currentLevel) {
        currentLevel->unload();
    }
    currentLevel = this;

    ifstream fin;
    if (id != -1) {    // if not default level
        fin.open(pathLevelRotations);
        if (!fin) {
            std::cout << "Couldn't open 'pathLevelRotations' [in Level::load()]\n";
        }
        else {
            string name = "rotation";
            int id;
            Vec3Df positionPlaced;
            Vec3Df linkedTo;
            int yRangeMin;
            int yRangeMax;
            Rotation* rotation;
            while (fin >> id) {
                fin >> positionPlaced.x;
                fin >> positionPlaced.y;
                fin >> positionPlaced.z;
                fin >> linkedTo.x;
                fin >> linkedTo.y;
                fin >> linkedTo.z;
                fin >> yRangeMin;
                fin >> yRangeMax;
                rotation = new Rotation(name, id, &(a.rotation), positionPlaced, linkedTo, yRangeMin, yRangeMax);
                levelRotations.push_back(rotation);
            }
            fin.close();
        }
        
        string name_;
        fin.open(pathLevelObjects);
        if (!fin) {
            std::cout << "Couldn't open 'pathLevelObjects' [in Level::load()]\n";
        }
        else {
            char buffer;
            bool isLinked;
            Object* object;
            Vec3Df linkedTo;
            Vec3Df positionPlaced;
            while (fin >> name_) {
                isLinked = false;
                fin >> positionPlaced.x;
                fin >> positionPlaced.y;
                fin >> positionPlaced.z;
                if (fin.peek() == '+') {
                    isLinked = true;
                    fin >> buffer;
                    fin >> linkedTo.x;
                    fin >> linkedTo.y;
                    fin >> linkedTo.z;
                }
                if (name_ == "axe") {
                    object = new Axe(name_, &(a.axe), positionPlaced);
                }
                else if (name_ == "door") {
                    object = new Door(name_, &(a.door), positionPlaced, isLinked, linkedTo);
                }
                levelObjects.push_back(object);
            }
            fin.close();
        }
        
        fin.open(pathLevelCharacters);
        if (!fin) {
            std::cout << "Couldn't open 'pathLevelCharacters' [in Level::load()]\n";
        }
        else {
            Vec3Df positionPlaced;
            Character* character;
            while (fin >> name_) {
                fin >> positionPlaced.x;
                fin >> positionPlaced.y;
                fin >> positionPlaced.z;
                if (name_ == "player") {
                    character = new Player(name_, &(a.pAttack), &(a.pClimb), &(a.pDash), &(a.pDeath), &(a.pHurt), &(a.pIdle), 
                            &(a.pJump), &(a.pRun), &(a.pAttackRun), &(a.pSkid), &(a.pWalk), &(a.pAttackWalk), &(a.directionIndicator),
                            positionPlaced);
                    playerPlaced = true;
                }
                levelCharacters.push_back(character);
            }
            fin.close();
        }
    }

    fin.open(pathLevelCells);
    if (!fin) {
        std::cout << "Couldn't open 'pathLevelCells' [in Level::load()]\n";
    }
    else {
        int width;
        int height;
        int depth;
        fin >> width;
        fin >> height;
        fin >> depth;
        fin.close();

        world.~World();
        world.create(pathLevelCells, width, height, depth);
    }
}

void Level::save(World& world) {
// come from filesystem commands, it picks the current level, if it's not nullptr, it gets here
// if id = -1 (default level), do a save as and pick a name and new id
// otherwise, ask if you want to save or save as...
// if save as ... pick new level id and name
// export from your lists to the appropriate files
// export from world to the appropriate file
// save as not only has to pick new id and name, but also update all the level paths
// actually dynamically create new level with constructor, and import lists from current level
// once you save, you add it to FileSystem::allLevels list and add to allLevelsBank
// then change current level to point to the new dynamically created one


// save() takes care of the writing protocol to the files from the lists. after saveAs(), you come here
    writeLevelCellsToFile(world);
    writeLevelObjectsToFile();
    writeLevelRotationsToFile();
    writeLevelCharactersToFile();
}

void Level::saveAs(World& world, Level*& currentLevel, int id_, string name_) {
    Level* level = new Level(id_, -1, name_);
    for (list<Rotation*>::iterator it = levelRotations.begin(); it != levelRotations.end(); ++it) {
        level->levelRotations.push_back(new Rotation(**it));  
    }
    for (list<Object*>::iterator it = levelObjects.begin(); it != levelObjects.end(); ++it) {
        level->levelObjects.push_back(new Object(**it));  
    }
    for (list<Character*>::iterator it = levelCharacters.begin(); it != levelCharacters.end(); ++it) {
        level->levelCharacters.push_back(new Character(**it));  
    }
    this->unload();
    currentLevel = level;
    currentLevel->save(world);
}

void Level::writeLevelCellsToFile(World& world) {
    world.save(pathLevelCells);
}

void Level::writeLevelObjectsToFile() {
    ofstream fout;
    fout.open(pathLevelObjects);
    if (!fout) {
        std::cout << "Couldn't open 'pathLevelObjects' [in Level::writeLevelObjectsToFile()]\n";
    }
    else {
        for (list<Object*>::iterator it=levelObjects.begin(); it != levelObjects.end(); ++it) {
            fout << " " << (*it)->name << " " << (*it)->orig.x << " " << (*it)->orig.y << " " << (*it)->orig.z;
            if ((*it)->isLinked) {
                fout << "+" << (*it)->linkedToOrig.x << " " << (*it)->linkedToOrig.y << " " << (*it)->linkedToOrig.z;
            }
        }
        fout.close();
    }
}

void Level::writeLevelRotationsToFile() {
    ofstream fout;
    fout.open(pathLevelRotations);
    if (!fout) {
        std::cout << "Couldn't open 'pathLevelRotations' [in Level::writeLevelRotationsToFile()]\n";
    }
    else {
        for (list<Rotation*>::iterator it=levelRotations.begin(); it != levelRotations.end(); ++it) {
            fout << " " << (*it)->id << " " << (*it)->orig.x << " " << (*it)->orig.y << " " << (*it)->orig.z << " "
                    << (*it)->linkedToOrig.x << " " << (*it)->linkedToOrig.y << " " << (*it)->linkedToOrig.z << " "
                    << (*it)->yRangeMin << " " << (*it)->yRangeMax;
        }
        fout.close();
    }
}

void Level::writeLevelCharactersToFile() {
    ofstream fout;
    fout.open(pathLevelCharacters);
    if (!fout) {
        std::cout << "Couldn't open 'pathLevelCharacters' [in Level::writeLevelCharactersToFile()]\n";
    }
    else {
    for (list<Character*>::iterator it=levelCharacters.begin(); it != levelCharacters.end(); ++it) {
        fout << " " << (*it)->name << " " << (*it)->orig.x << " " << (*it)->orig.y << " " << (*it)->orig.z;
    }
    fout.close();
    }
}
