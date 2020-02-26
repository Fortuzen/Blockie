#include <SDL.h>
#include <SDL_mixer.h>

#include <iostream>
#include <fstream>

#include "Game.h"
#include "Scene_Game.h"
#include "Scene_Gameover.h"

#include "IBlock.h"
#include "BLine.h"
#include "Block_J.h"
#include "Block_L.h"
#include "Block_O.h"
#include "Block_S.h"
#include "Block_T.h"
#include "Block_Z.h"

//TODO: Move this to better location
SDL_Texture* createTextOnDemand(const char* text) {
	SDL_Surface* surface_text = TTF_RenderText_Solid(Game::getInstance().font, text, SDL_Color{ 255,255,255 });
	SDL_Texture* text_TETRIS = SDL_CreateTextureFromSurface(Game::getInstance().renderer, surface_text);
	SDL_FreeSurface(surface_text);
	return text_TETRIS;
}

IBlock* Scene_Game::randomBlock() {
	IBlock* block = NULL;
	int i = std::rand() % blocks.size();
	block = blocks.at(i);

	return block;
}

void Scene_Game::start()
{
	name = "Game";

	//TODO
	// Inefficient?, make block factory
	IBlock* I = new BLine();
	I->init(Game::getInstance().renderer);
	IBlock* J = new Block_J();
	J->init(Game::getInstance().renderer);
	IBlock* L = new Block_L();
	L->init(Game::getInstance().renderer);
	IBlock* O = new Block_O();
	O->init(Game::getInstance().renderer);
	IBlock* S = new Block_S();
	S->init(Game::getInstance().renderer);
	IBlock* T = new Block_T();
	T->init(Game::getInstance().renderer);
	IBlock* Z = new Block_Z();
	Z->init(Game::getInstance().renderer);

	blocks.push_back(I);
	blocks.push_back(J);
	blocks.push_back(L);
	blocks.push_back(O);
	blocks.push_back(S);
	blocks.push_back(T);
	blocks.push_back(Z);

	particleManager.init(Game::getInstance().renderer);
	level.init(Game::getInstance().renderer);
	currentBlock = randomBlock();
	currentProcess = None;

	SDL_Log("Game scene init ok!");
}

void Scene_Game::update(double deltatime)
{
	Game& game = Game::getInstance();
	if (game.input.keyDown(SDLK_ESCAPE)) {
		game.gameStatus = Gameover;
	}

	if (currentBlock != NULL) {
		if (actionCooldown <= 0.0) {
			if (game.input.key(SDLK_LEFT)) {
				currentBlock->move(-1, 0);
				if (level.checkCollision(currentBlock)) {
					currentBlock->move(1, 0);
				}
			}
			else if (game.input.key(SDLK_RIGHT)) {
				currentBlock->move(1, 0);
				if (level.checkCollision(currentBlock)) {
					currentBlock->move(-1, 0);
				}
			}
			else if (Game::getInstance().input.key(SDLK_DOWN)) {
				moveDownTimer = -1.0;
			}

			actionCooldown = 0.05;
		}
		else {
			actionCooldown -= deltatime;
		}

		if (Game::getInstance().input.keyUp(SDLK_UP)) {
			currentBlock->rotate();
			if (level.checkCollision(currentBlock)) {
				bool ehto = level.findEmptySpot(currentBlock);
				if (!ehto) { for (int i = 0; i < 3; i++) currentBlock->rotate(); }
			}
		}



		if (moveDownTimer <= 0.0) {
			currentBlock->move(0, 1);
			moveDownTimer = Game::getInstance().levels[Game::getInstance().currentLevel];

			if (level.checkCollision(currentBlock)) {
				currentBlock->move(0, -1);
				level.joinBlock(currentBlock);
				level.findBlocksToRemove();
				if (level.blocksToRemove.empty()) {
					currentBlock = randomBlock();
					currentBlock->reset();
					if (level.checkCollision(currentBlock)) {
						game.gameStatus = Gameover;
					}
				}
				else {
					game.lines += level.blocksToRemove.size() / level.getWidth();
					if (game.lines >= game.levelLineCount[game.currentLevel] && game.currentLevel + 1 < 8) {
						game.currentLevel += 1;
					}
					//std::cout << lines << " " << currentLevel << "\n";
					currentProcess = DestroyBlocks;
					currentBlock = NULL;
				}


			}
		}
		else {
			moveDownTimer -= deltatime;
		}
	}

	if (currentProcess == DestroyBlocks) {
		if (level.blocksToRemove.empty()) {
			level.shiftBlocks();
			currentProcess = None;
			currentBlock = randomBlock();
			currentBlock->reset();

			if (level.checkCollision(currentBlock)) {
				game.gameStatus = Gameover;
			}
		}
		else if (destroyTimer <= 0) {
			Mix_PlayChannel(-1, game.resources.getSound("punch"), 0);
			SDL_Point p = level.removeNextBlock();
			game.score += 2 * level.blocksToRemove.size();
			destroyTimer = game.DESTROY_TIME;

			particleManager.createMachineAt((p.x + 1) * 32 + 16, (p.y + 1) * 32 + 16);

		}
		else {
			destroyTimer -= deltatime;
		}

	}
	particleManager.update(deltatime);


	if (game.gameStatus == Gameover) {
		if (game.score > game.highscore) {
			game.highscore = game.score;
			std::ofstream file;
			file.open("highscore.txt");
			file << std::to_string(game.highscore).c_str();
			file.close();
		}

		for (unsigned int i = 0; i < blocks.size(); i++) {
			blocks.at(i)->reset();
		}

		game.changeScene(new Scene_Gameover());
		return;
	}
}

void Scene_Game::render()
{
	Game& game = Game::getInstance();

	SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
	SDL_RenderClear(game.renderer);

	// Level
	level.render(game.renderer, game.LEVEL_OFFSET_X, game.LEVEL_OFFSET_Y, &blocks);
	// Current block
	if (currentBlock != NULL)
		currentBlock->render(game.renderer, game.LEVEL_OFFSET_X, game.LEVEL_OFFSET_Y);
	//Text
	SDL_Texture* it = game.resources.getText("tetris");
	SDL_Rect rect;
	rect.x = 32 * 14;
	rect.y = 32 * 1;
	SDL_QueryTexture(it, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(game.renderer, it, NULL, &rect);

	//Highscore
	SDL_Texture* hgs = game.resources.getText("highscore");
	rect.x = 32 * 13;
	rect.y = 32 * 3;
	SDL_QueryTexture(hgs, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(game.renderer, hgs, NULL, &rect);

	SDL_Texture* highscoreText = createTextOnDemand(std::to_string(game.highscore).c_str());
	rect.x = 32 * 14;
	rect.y = 32 * 5;
	SDL_QueryTexture(highscoreText, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(game.renderer, highscoreText, NULL, &rect);
	SDL_DestroyTexture(highscoreText);

	//Score
	SDL_Texture* s = game.resources.getText("score");
	rect.x = 32 * 13;
	rect.y = 32 * 7;
	SDL_QueryTexture(s, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(game.renderer, s, NULL, &rect);

	SDL_Texture* scoreText = createTextOnDemand(std::to_string(game.score).c_str());
	rect.x = 32 * 14;
	rect.y = 32 * 9;
	SDL_QueryTexture(scoreText, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(game.renderer, scoreText, NULL, &rect);
	SDL_DestroyTexture(scoreText);

	//Level
	SDL_Texture* l = game.resources.getText("level");
	rect.x = 32 * 13;
	rect.y = 32 * 11;
	SDL_QueryTexture(l, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(game.renderer, l, NULL, &rect);

	SDL_Texture* levelText = createTextOnDemand(std::to_string(game.currentLevel).c_str());
	rect.x = 32 * 14;
	rect.y = 32 * 13;
	SDL_QueryTexture(levelText, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(game.renderer, levelText, NULL, &rect);
	SDL_DestroyTexture(levelText);

	//Lines
	SDL_Texture* ll = game.resources.getText("lines");
	rect.x = 32 * 13;
	rect.y = 32 * 15;
	SDL_QueryTexture(ll, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(game.renderer, ll, NULL, &rect);

	SDL_Texture* lineText = createTextOnDemand(std::to_string(game.lines).c_str());
	rect.x = 32 * 14;
	rect.y = 32 * 17;
	SDL_QueryTexture(lineText, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(game.renderer, lineText, NULL, &rect);
	SDL_DestroyTexture(lineText);


	particleManager.render(game.renderer);

	SDL_RenderPresent(game.renderer);
}

void Scene_Game::close()
{
	currentBlock = NULL;
	for (IBlock* b : blocks) {
		delete b;
	}

	particleManager.close();
	
}
