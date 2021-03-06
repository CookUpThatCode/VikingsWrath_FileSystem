#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>
#include <fstream>

#include "Utility.h"
#include "Level.h"
#include "World.h"
#include "AssetManager.h"
#include "Object.h"

class FileSystem {    // remember, for a lot of these methods, when they have buttons, it needs to be grayed out
                      //if the button shouldn't be pressed at that time
public:
    FileSystem() {}
    ~FileSystem();
    void init();
    void loadLevel(int id_);
    void newLevel() {defaultLevel->load(currentLevel, world, a);}   // Engine::getInput. Engine will handle "Save first?" logic
    int getNextLevelID() {return (allLevels.empty() ? 1 : allLevels.back()->id + 1);}
    int getNextRotationID() {return (allRotations.empty() ? 1 : allRotations.back() + 1);}
    void saveLevel();
    void saveLevelAs(std::string name);         // Engine will have a getInput method to send the name here
    void removeLevelFromMap(int mapLevelNumber);
    void moveLevelToMap(Level* level, int mapLevelNumber_);
    void deleteLevelFromAllLevels(int id_); 
    void writeAllLevelsToFile();
    void writeAllRotationsToFile();
    void removeRotationFromLevel(int id_);
    void moveRotationToLevel(int id_, Vec3Df positionPlaced, Vec3Df linkedTo, int yRangeMin, int yRangeMax);
    void deleteRotationFromAllRotations(int id_);
    void createRotationAndAddToLevel(Vec3Df positionPlaced, Vec3Df linkedTo, int yRangeMin, int yRangeMax);
    void addObjectToLevel(std::string name, Vec3Df positionPlaced, bool isLinked, Vec3Df linkedTo);   // Engine will have a getInput method to send the name here
    void removeObjectFromLevel(Object* object);
    void changeLevelSize(int width, int height, int depth) {world.resize(width, height, depth);}
    const std::list<Object*>& getCurrentLevelObjects() {return currentLevel->levelObjects;}
    const std::list<Rotation*>& getCurrentLevelRotations() {return currentLevel->levelRotations;}
    const std::list<Character*>& getCurrentLevelCharacters() {return currentLevel->levelCharacters;}
    const Vec3Di& getSizeOfWorld() {return world.size;}
    const World& getWorld() {return world;}
    Character& getPlayer() {return *(currentLevel->levelCharacters.front());}
    const std::list<int>& getAllRotations() {return allRotations;}
    const std::list<Level*>& getAllLevels() {return allLevels;}
    bool displaySaveButton() {return (currentLevel->id == -1 ? false : true);}
    const std::array<Level*, 5>& getMapLevels() {return mapLevels;}
    void displayAreYouSureMessage();    // take care of implementing this
    void recordRotation();          // take care of implementing this
    void stopRecordingRotation();          // take care of implementing this

private:
    AssetManager a;
    World world;
    Level* currentLevel;
    Level* defaultLevel;
    std::array<Level*, 5> mapLevels;   
    std::string pathAllRotationsBank;
    std::string pathAllLevelsBank;
    std::list<int> allRotations;
    std::list<Level*> allLevels;

    std::list<Object*> menuRotationButtons;    
    std::list<Object*> menuLevelButtons;     
    std::list<Object*> menuOptionButtons;    
    std::list<Object*> menuTileButtons;    
    std::list<Object*> menuBlockButtons;
    std::list<Object*> menuCharacterButtons;
    std::list<Object*> menuObjectButtons;
};



#endif