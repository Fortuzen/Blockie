#pragma once
#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Input.h"
#include "Resources.h"
#include "Scene.h"



enum GAME_STATUS {
	Running,
	Paused,
	Gameover,
	Menu,
	Quit
};
enum PROCESSES {
	None,
	DestroyBlocks
};

class Game
{
public:
	static Game& getInstance() {
		static Game instance_;
		return instance_;
	}

	void init();
	void run();
	void reset();
	void close();

	void changeScene(Scene* newscene);

	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;

	Input input;
	Resources resources;

	GAME_STATUS gameStatus;
	Scene* scene;

	int highscore;
	int score;
	int lines;
	int currentLevel;

	int levelLineCount[8] = { 10, 20, 30, 40, 50, 60, 70, 80 };
	double levels[8] = { 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1 };
	
	const char* TITLE = "TETRIS";

	const int SCREEN_HEIGHT = 32 * 22;
	const int SCREEN_WIDTH = 32 * 20;
	const int LEVEL_OFFSET_X = 32;
	const int LEVEL_OFFSET_Y = 32;

	const double MOVEDOWN_TIME = 0.5;
	const double DESTROY_TIME = 0.1;

private:
	Game() {};
};

