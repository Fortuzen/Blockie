#include "Scene_Gameover.h"
#include "Scene_Mainmenu.h"

#include "Game.h"


void Scene_Gameover::start()
{
}

void Scene_Gameover::update(double deltatime)
{
	Game& game = Game::getInstance();
	if (Game::getInstance().input.keyDown(SDLK_RETURN)) {
		Game::getInstance().gameStatus = Menu;
		Game::getInstance().changeScene(new Scene_Mainmenu());
		return;
	}
}

void Scene_Gameover::render()
{
	Game& game = Game::getInstance();
	//Back rect	
	SDL_Rect rect;
	rect.w = 32 * 10;
	rect.h = 32 * 5;

	rect.x = 32 * 5;
	rect.y = 32 * 10;
	SDL_SetRenderDrawColor(Game::getInstance().renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(Game::getInstance().renderer, &rect);

	// Front
	rect.w = 32 * 8;
	rect.h = 32 * 3;

	rect.x = 32 * 6;
	rect.y = 32 * 11;
	SDL_SetRenderDrawColor(Game::getInstance().renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(Game::getInstance().renderer, &rect);

	// Text
	//Gameover
	SDL_Texture* it = Game::getInstance().resources.getText("gameover");
	rect.x = 32 * 7 - 16;
	rect.y = 32 * 12 - 16;
	SDL_QueryTexture(it, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(Game::getInstance().renderer, it, NULL, &rect);

	SDL_RenderPresent(Game::getInstance().renderer);
}

void Scene_Gameover::close()
{
}
