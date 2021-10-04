// --- Object.cpp ---

#include "Object.h"

#include <iostream>

using std::string;
using std::list;

Object::Object(string name, Graphics* sprite) 
    : name(name), sprite(sprite)
{}

Object::Object(string name) 
    : name(name)
{}

Character::Character(std::string name, Graphics* attack, Graphics* climb, Graphics* dash, Graphics* death, Graphics* hurt, Graphics* idle, 
            Graphics* jump, Graphics* run, Graphics* attackRun, Graphics* skid, Graphics* walk, Graphics* attackWalk, 
            Graphics* directionIndicator, Vec3Df positionPlaced)
    : Object(name, nullptr), attack(attack), climb(climb), dash(dash), death(death), hurt(hurt), idle(idle), jump(jump),
            run(run), attackRun(attackRun), skid(skid), walk(walk), attackWalk(attackWalk), directionIndicator(directionIndicator) { 

    orig = positionPlaced;
}

Player::Player(string name, Graphics* attack, Graphics* climb, Graphics* dash, Graphics* death, Graphics* hurt, Graphics* idle, 
        Graphics* jump, Graphics* run, Graphics* attackRun, Graphics* skid, Graphics* walk, Graphics* attackWalk, 
        Graphics* directionIndicator, Vec3Df positionPlaced)
    : Character(name, attack, climb, dash, death, hurt, idle, jump, run, attackRun, skid, walk, attackWalk, 
            directionIndicator, positionPlaced) {

    dims = {34.0f, 52.0f, 34.0f};
    spriteDims = {112.0f, 80.0f};
    drawingOffset = {-40.0f, -80.0f};
    attackDims = {72.0f, 52.0f, 34.0f};
}

Rotation::Rotation(std::string name, int id, Vec3Df positionPlaced, Vec3Df linkedTo, int yRangeMin, int yRangeMax)
    : Object(name) {

    this->id = id;
    orig = positionPlaced;
    linkedToOrig = linkedTo;
    this->yRangeMin = yRangeMin;
    this->yRangeMax = yRangeMax;
    dims = {54.0f, 54.0f, 54.0f};
    spriteDims = {54.0f, 54.0f};
    pathRotation = "./Files/rotation_" + std::to_string(id) + "_.txt";
}

Rotation::Rotation(std::string name, int id, Graphics* sprt, Vec3Df positionPlaced, Vec3Df linkedTo, int yRangeMin, int yRangeMax)
    : Object(name) {

    this->id = id;
    orig = positionPlaced;
    linkedToOrig = linkedTo;
    this->yRangeMin = yRangeMin;
    this->yRangeMax = yRangeMax;
    dims = {54.0f, 54.0f, 54.0f};
    spriteDims = {54.0f, 54.0f};
    pathRotation = "./Files/rotation_" + std::to_string(id) + "_.txt";

    sprite = sprt;
}



Axe::Axe(string name, Graphics* sprite, Vec3Df positionPlaced)
    : Object(name, sprite) {

    orig = positionPlaced;
    dims = {32.0f, 32.0f, 54.0f};
    spriteDims = {32.0f, 32.0f};
}

Door::Door(string name, Graphics* sprite, Vec3Df positionPlaced, bool isLinked, Vec3Df linkedTo)
    : Object(name, sprite) {
    
    orig = positionPlaced;
    this->isLinked = isLinked;
    linkedToOrig = linkedTo;
    dims = {54.0f, 40.0f, 54.0f};
    spriteDims = {54.0f, 40.0f};
}
