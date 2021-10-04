#include "olcPixelGameEngine.h"
#include "Engine.h"

int main()
{
	Engine game;
	if (game.Construct(512, 448, 1, 1))
		game.Start();
	return 0;
}


