#ifndef ANIMATION_H
#define ANIMATION_H

#include "olcPixelGameEngine.h"

class Graphics;

class Animation {
public:
    Animation(int numFrames, float frameLength, float waitAtEnd)
        :numFrames(numFrames), frameLength(frameLength), waitAtEnd(waitAtEnd) {}

    int numFrames;
    float frameLength;
    float waitAtEnd;
    bool busy = false;
};



#endif