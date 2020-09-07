#ifndef LEVEL_H
#define LEVEL_H

#include "Object.h"

class FileSystem;

class Level {
public:
    Level(FileSystem* f, int id, int mapLevelNumber, std::string name);
    ~Level();
    void load();
    void save();

    int id;
    int mapLevelNumber;
    std::string name;

    std::string pathLevelCells;
    std::string pathLevelObjects;
    std::string pathLevelRotations;
    std::string pathLevelCharacters;

    std::list<Rotation*> levelRotations;
    std::list<Object*> levelObjects;
    std::list<Character*> levelCharacters;

private:
    FileSystem* f;

};



#endif