// --- Assets.h ---

#ifndef ASSETS_H
#define ASSETS_H

#include "Utility.h"
#include <map>
#include "Object.h"
#include "Graphics.h"

class Engine;

class AssetManager {
public:
    AssetManager() {}
    ~AssetManager();
    void init();

    std::list<Object*> allObjectTypes;
    Graphics directionIndicator;
    
    Graphics pIcon;
    Graphics pAttack;
    Graphics pClimb;
    Graphics pDash;
    Graphics pDeath;
    Graphics pHurt;
    Graphics pIdle;
    Graphics pJump;
    Graphics pRun;
    Graphics pAttackRun;
    Graphics pSkid;
    Graphics pWalk;
    Graphics pAttackWalk;

    Graphics rotationIcon;
    Graphics rotation;

    Graphics axeIcon;
    Graphics axe;
};




#endif