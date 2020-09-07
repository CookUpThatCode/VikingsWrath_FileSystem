#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "olcPixelGameEngine.h"

#include "Animation.h"
#include "ObjectType.h"

class Graphics {
public:
    Graphics() {}
    ~Graphics();
    void load(std::string filename);

    olc::Sprite* sprite = nullptr;
    olc::Decal* decal = nullptr;
    Animation* animation = nullptr;
    ObjectType* objectType = nullptr;
};



#endif