// --- Assets.cpp ---

#include "AssetManager.h"

#include "olcPixelGameEngine.h"
#include "Utility.h"
#include "Object.h"
#include "Engine.h"

using namespace std;

AssetManager::~AssetManager() {

}

void AssetManager::init(Engine* engine) {
    e = engine;

    toObject["player"] = PLAYER;


    // testDragDeath.load("./Sprites/enSmallDragon/dragDeath.png");           FIX THIS ONE !
    testDragDeath.load("./Sprites/player/pRunAtk.png");
}

void AssetManager::registerObject(ObjectTypeEnum otEnum) {
    if (otEnum == PLAYER) {
        Player* player = new Player("player");
        g->l->objects.push_back(player);
    }
    else if (otEnum == DEMON) {
        
    }
    else if (otEnum == MEDUSA) {
        
    }
    else if (otEnum == DRAGON) {
        
    }


    // switch(object) {
    //     case PLAYER:
    //         Player* player = new Player();
    //         g->l->objects.push_back(player);
    //         break;
    //     case DEMON:
    //     //     break;
    //     // case MEDUSA:
    //     //     break;
    //     // case DRAGON:
    //     //     break;
    //     // default:
    //     //     3+4;
    // }
}

void AssetManager::addAsset(std::string fileName, int numFrames, float frameLength, float waitAtEnd) {

}

void AssetManager::addAsset(std::string fileName) {

}
