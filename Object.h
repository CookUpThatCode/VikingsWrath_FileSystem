// --- Object.h ---

#ifndef OBJECT_H
#define OBJECT_H

#include "Utility.h"
#include "Graphics.h"

class FileSystem;

class Object {
public:
    Object(std::string name, Graphics* sprite);
    Object(std::string name); 
    ~Object() {}
    virtual void onInteract(Object* actedUponBy) {}
    virtual void addLink(float x, float y, float z) {}
    virtual void setPathRotation(int id) {}
    virtual void initPoints(int div) {}
    virtual void update(float x, float y, float z) {}
    int getID() {return id;}
    
    bool isFriendly = true;
    bool isLinked = false;
    bool solidToMap = false;
    bool solidToPlayer = false;
    bool solidToNPC = false;    // NPC means Non-Player Characters: enemies, and guides
    bool active = false;        // used for Rotation, for example
    bool takingControls = false;
    bool subjectToGravity = false;

    int id;                         // only for rotations
    std::string name;
    Vec3Df orig;  // origin
    Vec3Df linkedToOrig;
    int yRangeMin;
    int yRangeMax;
    std::string pathRotation;

protected:
    Graphics* sprite;
    Vec3Df dims;  // dimensions
    Vec2Df spriteDims;
    Vec3Df drawingOrig;
    Vec3Df points[8];
    Vec3Df gravity;
    Vec3Df velocity;
    int damageToInflict;
};

class Character : public Object {
public:
    Character(std::string name, Graphics* attack, Graphics* climb, Graphics* dash, Graphics* death, Graphics* hurt, Graphics* idle, 
            Graphics* jump, Graphics* run, Graphics* attackRun, Graphics* skid, Graphics* walk, Graphics* attackWalk, 
            Graphics* directionIndicator, Vec3Df positionPlaced);
    void initPoints(int div) override {}
    void update(float x, float y, float z) override {}
    void onInteract(Object* actedUponBy) override {}
    void testing() {}                                                        // this is temporary. draw boxes around character for collision, attacks, etc.

protected:
    Vec3Df attackDims;
    std::vector<Vec3Df> extraPoints;
    int directionIndicatorIndex;
    float directionIndicatorAngle;
    Graphics* directionIndicator;
    SpriteDirection spriteDir;
    Vec2Df drawingOffset;
    Graphics* attack;
    Graphics* climb;
    Graphics* dash;
    Graphics* death;
    Graphics* hurt;
    Graphics* idle;
    Graphics* jump;
    Graphics* run;
    Graphics* attackRun;
    Graphics* skid;
    Graphics* walk;
    Graphics* attackWalk;
    State state;
};

class Player : public Character {
public:
    Player(std::string name, Graphics* attack, Graphics* climb, Graphics* dash, Graphics* death, Graphics* hurt, Graphics* idle, 
            Graphics* jump, Graphics* run, Graphics* attackRun, Graphics* skid, Graphics* walk, Graphics* attackWalk, 
            Graphics* directionIndicator, Vec3Df positionPlaced); 
};

class Rotation : public Object {
public:
    Rotation(std::string name, int id, Vec3Df positionPlaced, Vec3Df linkedTo, int yRangeMin, int yRangeMax);
    Rotation(std::string name, int id, Graphics* sprt, Vec3Df positionPlaced, Vec3Df linkedTo, int yRangeMin, int yRangeMax);
    void onInteract(Object* actedUponBy) override {}
    void addLink(float x, float y, float z) override {}
    void setPathRotation(int id) override {}
    void initPoints(int div) override {}
    void update(float x, float y, float z) override {}

};

class Axe : public Object {
public:
    Axe(std::string name, Graphics* sprite, Vec3Df positionPlaced);
    void onInteract(Object* actedUponBy) override {}
    void addLink(float x, float y, float z) override {}
    void initPoints(int div) override {}
    void update(float x, float y, float z) override {} 
};

class Door : public Object {
public:
    Door(std::string name, Graphics* sprite, Vec3Df positionPlaced, bool isLinked, Vec3Df linkedTo);
    void onInteract(Object* actedUponBy) override {}
    void addLink(float x, float y, float z) override {}
    void initPoints(int div) override {}
    void update(float x, float y, float z) override {}
};





#endif