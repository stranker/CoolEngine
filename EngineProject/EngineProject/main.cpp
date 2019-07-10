#include "Game.h"
#include <iostream>
#include "TextureImporter.h"
int main()
{
	Game* game = new Game(800,600,"Test");

	if (game->Start())
	{
		game->Loop();
	}
	game->Stop();
	std::cin.get();
	std::cin.get();
	delete game;
	return 0;
}