// --- UTILITY.h ---

#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include "olcPixelGameEngine.h"
#include <map>


// ------------------- Structs ------------------

// struct Gfx    // Graphics: convenient way to load an image as both a sprite and a decal at the same time
// {
// 	Gfx() { }
// 	~Gfx()
// 	{
// 		delete sprite;
// 		delete decal;
// 	}
// 	void load(std::string filename)
// 	{
// 		sprite = new olc::Sprite(filename);
// 		decal = new olc::Decal(sprite);
// 	}
// 	olc::Sprite* sprite = nullptr;
// 	olc::Decal* decal = nullptr;
// };



struct Vec3Df    // points and vectors in 3-dimensional space
{
	float x, y, z;
};

struct Vec3Di
{
	int x, y, z;
};

struct Vec2Df    
{
	float x, y;
};

struct Vec2Di
{
	int x, y;
};

struct Quad     // collections of 4 points. each has a tile with sprite info
{
	Vec3Df points[4];
	olc::vi2d tileSpr;    // location on sprite sheet
	olc::vi2d tileDims;   // dimensions of tile on sprite sheet
};

struct Cell    // collection of 6 faces, each with tile coordinates on sprite sheet
{
	bool placed = false;
	//olc::vi2d tiles[6]{ };   // sprite sheet coordinates for 6 faces
	int tiles[6];
};


// ------------------- Enums --------------

enum Face
{
	FLOOR = 0,
	EAST = 1,
	NORTH = 2,
	WEST = 3,
	SOUTH = 4,
	TOP = 5
};

enum SpriteDirection {
	LEFT,
	RIGHT
};

enum State {
	WALKING,
	RUNNING     // ... ETC
};

enum Mode {
	MAP,
	LEVEL,
	DESIGNER,
	SPRITE_SELECTOR,
	MENU
};








#endif
