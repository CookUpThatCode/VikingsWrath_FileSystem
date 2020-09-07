// --- Object.h ---

#ifndef OBJECT_H
#define OBJECT_H

#include "Utility.h"
#include "Graphics.h"

class FileSystem;

class Object {
public:
    Object(std::string name, Graphics* sprite);
    ~Object() {}
    virtual void onInteract(Object* actedUponBy) {}
    virtual void addLink(float x, float y, float z) {}
    virtual void setPathRotation(int id) {}
    virtual void initPoints(ind div);
    virtual void update(float x, float y, float z);
    
    bool isFriendly = true;
    bool isLinked = false;
    bool solidToMap = false;
    bool solidToPlayer = false;
    bool solidToNPC = false;    // NPC means Non-Player Characters: enemies, and guides
    bool active = false;        // used for Rotation, for example
    bool takingControls = false;
    bool subjectToGravity = false;

protected:
    std::string name;
    int id;                         // only for rotations
    Graphics* sprite;
    std::string pathRotation;
    Vec3Df orig;  // origin
    Vec3Di dims;  // dimensions
    Vec2Di spriteDims;
    Vec3Df drawingOrig;
    Vec3Df linkedToOrigin;
    Vec3Df points[8];
    Vec3Df gravity;
    Vec3Df velocity;
    int damageToInflict;
};

class Character : public Object {
public:
    Character();
    void initPoints(int div) override;
    void update(float x, float y, float z) override;
    void onInteract(Object* actedUponBy) override;
    void testing();                                                        // this is temporary. draw boxes around character for collision, attacks, etc.

protected:
    Vec3Di attackDims;
    std::vector<Vec3Df> extraPoints;
    int directionIndicatorIndex;
    float directionIndicatorAngle;
    Graphics* directionIndicator;
    SpriteDirection spriteDir;
    Vec2Di drawingOffset;
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
            Graphics* directionIndicator); 
};

class Rotation : public Object {
public:
    Rotation(std::string name, int id, Graphics* sprite);
    void onInteract(Object* actedUponBy) override;
    void addLink(float x, float y, float z) override;
    void setPathRotation(int id) override;
    void initPoints(ind div) override;
    void update(float x, float y, float z) override;
};

class Axe : public Object {
    Axe(std::string name, Graphics* sprite);
    void onInteract(Object* actedUponBy) override;
    void addLink(float x, float y, float z) override;
    void initPoints(ind div) override;
    void update(float x, float y, float z) override;  
};





#endif