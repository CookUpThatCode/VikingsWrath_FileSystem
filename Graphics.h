#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "olcPixelGameEngine.h"


class Graphics {
public:
    Graphics() {}
    ~Graphics() {
        delete sprite;
        delete decal;
    }
    void load(std::string filename) {
        sprite = new olc::Sprite(filename);
        decal = new olc::Decal(sprite);
    }

    olc::Sprite* sprite = nullptr;
    olc::Decal* decal = nullptr;

    int numFrames;
    float frameLength;
    float waitAtEnd;
    bool busy = false;
};



#endif