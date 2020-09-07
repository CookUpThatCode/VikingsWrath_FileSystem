#include "Level.h"
#include "Engine.h"
#include "utility.h"
#include <stdio.h>

using namespace std;

Level::Level(FileSystem* f, int id, int mapLevelNumber, string name) 
    : f(f), id(id), name(name), mapLevelNumber(mapLevelNumber) {
    pathLevelCells = "./Files/level_" + to_string(id) + "_cells.txt";
    pathLevelObjectsBank = ".Files/level_" + to_string(id) + "_objects.txt";
    pathLevelRotationsBank = ".Files/level_" + to_string(id) + "_rotations.txt";
    pathLevelCharactersBank = ".Files/level_" + to_string(id) + "_characters.txt";

    std::string buffer;
    f->fin.open(pathLevelObjectsBank);
    fin >>

    f->fin.close();

    pathRotationsList = pathLevel + "rotationsList";
    pathObjects = pathLevel + "objects";
    pathLevel += ".txt";
    pathRotationsList += ".txt";
    pathObjects += ".txt";

    string pathRotation;
    g->fin.open(pathRotationsList);
    while(g->fin >> pathRotation) {
        pathRotations.push_back(pathRotation);
    }
    g->fin.close();
}

void Level::load() {
    if (g->l) {
        g->l->unload();
    }
    g->l = this;

    string buffer;
    float x, y, z;
    char ch;
    g->fin.open(pathObjects);
    while(g->fin >> buffer) {
        g->a.createObject(g->a.toObject[buffer]);
        g->fin >> x;
        g->fin >> y;
        g->fin >> z;
        objects.back()->origin = {x, y, z};
        if(g->fin.peek() == '*') {
            g->fin >> ch;
            g->fin >> x;
            g->fin >> y;
            g->fin >> z;
            objects.back()->linkOrigin = {x, y, z};
        }
    }
    g->fin.close();
}

void Level::unload() {
    std::vector<Object*>().swap(objects);       // deletes and deallocates memory of vector
}

void Level::save() {
    g->fout.open(pathLevel);
        g->fout << g->world.size.x << " " << g->world.size.y << " " << g->world.size.z << " ";
        for (int x = 0; x < g->world.size.x; x++)
            for (int y = 0; y < g->world.size.y; y++)
                for (int z = 0; z < g->world.size.z; z++)
                    g->fout << (g->world.cells[x][y][z].placed ? 1 : 0) << " ";
    g->fout.close();

    g->fout.open(pathObjects);
    for (unsigned i=0; i<objects.size(); ++i) {
        g->fout << objects[i]->name << " " << objects[i]->origin.x << " " << objects[i]->origin.y << " " << objects[i]->origin.z;
        if (objects[i]->linkTo) {
            g->fout << "*" << objects[i]->linkOrigin.x << " " << objects[i]->linkOrigin.y << " " << objects[i]->linkOrigin.z << " ";
        }
        else {
            g->fout << " ";
        }
    }
    g->fout.close();
}

void Level::close() {
    
}

void Level::newLevel() {                     // ask if want to save, unload previous one, and save new level with all info
    int i = findAvailableIdx();
    Level* level = new Level(g, i);
    g->l = level;
    g->f.levels.push_back(level);
}

void Level::removeLevelFromMap() {
    mapSlot = -1;
}

void Level::deleteLevelFromBank() {
    for (unsigned i=0; i < g->f.levels.size(); ++i) {
        if (g->f.levels[i]->idx == idx) {
            g->f.levels.erase(g->f.levels.begin() + int(i));
        }
    }

    int index;
    g->fin.open(g->f.pathLevelsBank);
    while (g->fin >> index) {
        if (index == idx) {
            remove(pathLevel.c_str());
        }
    }
    g->fin.close();

    g->fout.open(g->f.pathLevelsBank);
    for (unsigned i=0; i < g->f.levels.size(); ++i) {
        g->fout << g->f.levels[i]->idx << " ";
    }
    g->fout.close();
}

int Level::findAvailableIdx() {
    int x=0;
    for (unsigned i=0; i < g->f.levels.size(); ++i) {
        if (g->f.levels[i]->idx > x) {
            return g->f.levels[i]->idx;
        }
        ++x;
    }
    return g->f.levels.back()->idx + 1;
}

void Level::addRotation(int idx) {

}

void Level::deleteRotation(int idx) {

}

void Level::addObject() {

}

void Level::deleteObject() {

}