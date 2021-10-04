// --- World.h ---

#ifndef WORLD_H
#define WORLD_H

#include <fstream>

#include "Utility.h"

class FileSystem;

class World
{
public:
	World() {}
	~World();
	void create(const std::string& pathLevelCells, int width, int height, int depth);
	void save(const std::string& pathLevelCells);
	void resize(int width, int height, int depth);
	void destroy();
	Cell& getCell(const Vec3Di& location);
	
	Vec3Di size;
	Cell*** cells = nullptr;
	Cell nullCell;

};




#endif
