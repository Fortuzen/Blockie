#include <iostream>

#include "Scene_Mainmenu.h"
#include "Scene_Game.h"

void Scene_Mainmenu::start()
{
	p_game = &Game::getInstance();

	name = "Mainmenu";
	scrollingText = new ScrollingText();
	scrollingText->init(Game::getInstance().renderer,
		("HIGHSCORE: " + std::to_string(Game::getInstance().highscore)).c_str(),
		Game::getInstance().SCREEN_WIDTH, Game::getInstance().SCREEN_HEIGHT,
		128, 500, -200);

}

void Scene_Mainmenu::update(double deltatime)
{
	Game& game = Game::getInstance();
	
	if (game.input.keyDown(SDLK_RETURN)) {
		game.gameStatus = Running;
		game.score = 0;
		game.lines = 0;
		game.currentLevel = 0;
		game.changeScene(new Scene_Game());
		return;
	}
	scrollingText->update(deltatime);
}

void Scene_Mainmenu::render()
{
	Game& game = Game::getInstance();
	SDL_RenderClear(game.renderer);
	SDL_Texture* menu = game.resources.getTexture("mainmenu");
	SDL_RenderCopy(game.renderer, menu, NULL, NULL);

	SDL_Texture* text = game.resources.getText("mainmenu_start");
	SDL_Rect rect;
	rect.x = 32 * 3;
	rect.y = 32 * 18;
	SDL_QueryTexture(text, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(game.renderer, text, NULL, &rect);

	scrollingText->render(game.renderer);

	SDL_RenderPresent(game.renderer);
}

void Scene_Mainmenu::close()
{
	delete scrollingText;
}
