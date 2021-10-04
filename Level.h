#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>

#include "Object.h"
#include "utility.h"

class FileSystem;
class World;
class AssetManager;

class Level {
public:
    Level(int id, int mapLevelNumber, std::string name);   
    ~Level();
    void load(Level*& currentLevel, World& world, AssetManager& a);
    void unload();    // same as destructor but keeps the other variables, only destroys the lists
    void save(World& world);
    void saveAs(World& world, Level*& currentLevel, int id_, std::string name_);
    void addToMap(int mapLevelNumber_) {mapLevelNumber = mapLevelNumber_;}
    void writeLevelCellsToFile(World& world);
    void writeLevelObjectsToFile();
    void writeLevelRotationsToFile();
    void writeLevelCharactersToFile();

    int id;
    int mapLevelNumber;
    std::string name;
    bool playerPlaced;

    std::string pathLevelCells;
    std::string pathLevelObjects;
    std::string pathLevelRotations;
    std::string pathLevelCharacters;

    std::list<Rotation*> levelRotations;
    std::list<Object*> levelObjects;
    std::list<Character*> levelCharacters;

};



#endif