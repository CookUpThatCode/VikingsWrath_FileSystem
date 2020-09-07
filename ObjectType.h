#ifndef OBJECTTYPE_H
#define OBJECTTYPE_H

#include "olcPixelGameEngine.h"
#include "utility.h"

class Graphics;
enum ObjectTypeEnum;

class ObjectType {
public:
    ObjectType(std::string name, ObjectTypeEnum otEnum, Graphics* icon)
        :name(name), otEnum(otEnum), icon(icon) {}
    ~ObjectType() {}

    Graphics* icon;
    ObjectTypeEnum otEnum;
    std::string name;
};



#endif