#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H


#include "Utility.h"
#include "Object.h"
#include "Graphics.h"

class Engine;

class AssetManager {
public:
    AssetManager() {}
    void init(std::list<Object*>& menuRotationButtons, std::list<Object*>& menuLevelButtons, std::list<Object*>& menuOptionButtons, 
            std::list<Object*>& menuTileButtons, std::list<Object*>& menuBlockButtons, std::list<Object*>& menuCharacterButtons, 
            std::list<Object*>& menuObjectButtons);
 
    Graphics directionIndicator;
    
    Graphics levelIcon;
    Graphics rotationIcon;
    Graphics pIcon;
    Graphics axeIcon;
    Graphics doorIcon;

    Graphics saveIcon;
    Graphics saveAsIcon;
    Graphics newLevelIcon;
    Graphics changeLevelSizeIcon;

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

    Graphics rotation;
    Graphics axe;
    Graphics door;
};




#endif