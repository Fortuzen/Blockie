#include <iostream>

#include "Game.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include <fstream>

#include "Resources.h"
#include "Scene_Mainmenu.h"

void Game::init()
{

	//SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//SDL TTF
	TTF_Init();
	font = TTF_OpenFont("m5x7.ttf", 64);
	// MIXER
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 2048);
	// Image
	IMG_Init(IMG_INIT_PNG);

	input.init();
	resources.init();


	// Load highscore from file
	std::ifstream file;
	file.open("highscore.txt");
	if (!file) {
		std::ofstream ofile;
		ofile.open("highscore.txt");
		ofile << "0";
		ofile.close();
	}
	else {
		file >> highscore;
	}
	file.close();

	score = 0;
	lines = 0;
	currentLevel = 0;

	gameStatus = Menu;
	// Don't worry. It is deleted when scene is changed.
	changeScene(new Scene_Mainmenu());

	SDL_Log("Game init ok!");

}

void Game::run()
{

	Mix_PlayMusic(resources.getMusic("music_1"), -1);

	Uint32 end = SDL_GetTicks();
	double deltaTime = 0;
	while (gameStatus != Quit) {
		Uint32 start = SDL_GetTicks();
		input.update();
		if (input.quit()) {
			gameStatus = Quit;
		}
		if (input.keyDown(SDLK_p)) {
			if (gameStatus == Paused && gameStatus != Menu) {
				gameStatus = Running;
			}
			else if (gameStatus != Menu) {
				gameStatus = Paused;
			}
		}
		if (gameStatus != Paused) {
			scene->update(deltaTime);
		}	
		scene->render();

		end = SDL_GetTicks();
		deltaTime = (double)(end - start) / 1000;
		//std::cout << deltaTime << "\n";
	}


}

void Game::reset()
{
}

void Game::close()
{
	if (scene) {
		scene->close();
		delete scene;
	}

	resources.clear();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

void Game::changeScene(Scene * newscene)
{
	if (scene) {
		scene->close();
		delete scene;
	}
	scene = newscene;
	scene->start();
}
