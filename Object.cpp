// --- Object.cpp ---

#include "Object.h"

#include <iostream>

using std::string;
using std::list;

#include "FileSystem.h"

Object::Object(string name, Graphics* sprite) 
    : name(name), sprite(sprite)
{}

Player::Player(string name, Graphics* attack, Graphics* climb, Graphics* dash, Graphics* death, Graphics* hurt, Graphics* idle, 
        Graphics* jump, Graphics* run, Graphics* attackRun, Graphics* skid, Graphics* walk, Graphics* attackWalk, 
        Graphics* directionIndicator)
    : Object(name, nullptr), attack(attack), climb(climb), dash(dash), death(death), hurt(hurt), idle(idle), jump(jump),
            run(run), attackRun(attackRun), skid(skid), walk(walk), attackWalk(attackWalk), directionIndicator(directionIndicator) {
    dims = {34, 52, 34};
    spriteDims = {112, 80};
    drawingOffset = {-40, -80};
    attackDims = {72, 52, 34};
}


Rotation::Rotation(string name, int id, Graphics* sprite)
    : Object(name, sprite), id(id) {
    dims = {54, 54, 54};
    spriteDims = {54, 54};
}

Axe::Axe(string name, Graphics* sprite)
    : Object(name, sprite) {
    dims = {32, 32, 54};
    spriteDims = {32, 32};
}