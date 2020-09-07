#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Utility.h"
#include "Level.h"
#include "World.h"
#include "AssetManager.h"
#include "Object.h"
#include <fstream>

class FileSystem {
public:
    FileSystem() {}
    ~FileSystem();
    void init();
    void loadLevel(int id);
    void newLevel(int id);
    int getNextLevelID();
    int getNextRotationID();
    void saveLevel();
    void saveLevelAs();
    void removeLevelFromMap(int mapLevelNumber);
    void moveLevelToMap(int mapLevelNumber);
    void deleteLevelFromAllLevelsBank(int id);
    void pushAllLevelsToBank();
    void removeRotationFromLevel(int id);
    void moveRotationToLevel(int id);
    void deleteRotationFromAllRotationsBank(int id);
    void pushAllRotationsToBank();
    void createRotation(int id);
    void getPathOfRotation(int id);
    void getPathOfLevel(int id);
    void addObjectToLevel();
    void changeLevelSize(int x, int y, int z);
    const std::list<Object*>& getCurrentLevelObjects();
    const std::list<Rotation*>& getCurrentLevelRotations();
    const std::list<Character*>& getCurrentLevelCharacters();
    const Vec3Di& getSizeOfWorld();
    const World& getWorld();
    Player& getPlayer();
    std::string getPathRotation(int id);


private:
    std::ofstream fout;
    std::ifstream fin;
    AssetManager a;
    World world;
    Level* currentLevel;
    Level* defaultLevel;
    Level* mapLevels[5];   
    std::string pathAllRotationsBank;
    std::string pathAllLevelsBank;
    std::list<int> allRotations;
    std::list<Level*> allLevels;
    int highestLevelID;
    int highestRotationID;
};



#endif