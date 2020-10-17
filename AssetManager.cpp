// --- Assets.cpp ---

#include "AssetManager.h"

#include "olcPixelGameEngine.h"
#include "Utility.h"
#include "Object.h"
#include "Engine.h"

using namespace std;

        // testDragDeath.load("./Sprites/enSmallDragon/dragDeath.png");           FIX THIS ONE !
void AssetManager::init(std::list<Object*>& menuRotationButtons, std::list<Object*>& menuLevelButtons, 
            std::list<Object*>& menuOptionButtons, std::list<Object*>& menuTileButtons, std::list<Object*>& menuBlockButtons, 
            std::list<Object*>& menuCharacterButtons, std::list<Object*>& menuObjectButtons) {
    menuOptionButtons.push_back(new Object("saveButton", &saveIcon));
    menuOptionButtons.push_back(new Object("saveAsButton", &saveAsIcon));
    menuOptionButtons.push_back(new Object("newLevelButton", &newLevelIcon));
    menuOptionButtons.push_back(new Object("changeLevelSizeButton", &changeLevelSizeIcon));

    // For every object, add its type to the list, so that the icons will populate to the object selector
    menuObjectButtons.push_back(new Object("axeButton", &axeIcon));
    menuObjectButtons.push_back(new Object("doorButton", &doorIcon));
    menuObjectButtons.push_back(new Object("rotationButton", &rotationIcon));    


    menuCharacterButtons.push_back(new Object("playerButton", &pIcon));

    // fix these png filenames to match what's below

    // Object icons (not including Characters) and Level icon
    levelIcon.load("./Sprites/objects/levelIcon.png");
    rotationIcon.load("./Sprites/objects/rotationIcon.png");
    axeIcon.load("./Sprites/objects/axeIcon.png");
    doorIcon.load("./Sprites/objects/doorIcon.png");

    saveIcon.load("./Sprites/objects/saveIcon.png");
    saveAsIcon.load("./Sprites/objects/saveAsIcon.png");
    newLevelIcon.load("./Sprites/objects/newLevelIcon.png");
    changeLevelSizeIcon.load("./Sprites/objects/changeLevelSizeIcon.png");
    

    // Character icons
    pIcon.load("./Sprites/objects/pIcon.png");

    // Objects (not including Characters)
    rotation.load("./Sprites/objects/rotation.png");
    axe.load("./Sprites/objects/axe.png");
    door.load("./Sprites/objects/door.png");

    // Characters, listed individually below:
    // Player
    pAttack.load("./Sprites/player/pAttack.png");
    pClimb.load("./Sprites/player/pClimb.png");
    pDash.load("./Sprites/player/pDash.png");
    pDeath.load("./Sprites/player/pDeath.png");
    pHurt.load("./Sprites/player/pHurt.png");
    pIdle.load("./Sprites/player/pIdle.png");
    pJump.load("./Sprites/player/pJump.png");
    pRun.load("./Sprites/player/pRun.png");
    pAttackRun.load("./Sprites/player/pAttackRun.png");
    pSkid.load("./Sprites/player/pSkid.png");
    pWalk.load("./Sprites/player/pWalk.png");
    pAttackWalk.load("./Sprites/player/pAttackWalk.png");
    directionIndicator.load("./Sprites/player/directionIndicator.png");


}
