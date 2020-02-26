#include "Game.h"

int main(int argc, char* argv[]) {
	
	Game& game = Game::getInstance();
	game.init();
	game.run();
	game.close();
	return 0;
}