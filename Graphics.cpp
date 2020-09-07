#include "Graphics.h"

using namespace std;

Graphics::~Graphics() {
    delete sprite;
    delete decal;
}

void Graphics::load(string filename) {
    sprite = new olc::Sprite(filename);
    decal = new olc::Decal(sprite);
}