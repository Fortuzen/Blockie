#pragma once
#include <queue>
#include <SDL.h>
#include "IBlock.h"

class Level {
public:
	Level() {};
	~Level() {};
	void init(SDL_Renderer* r);
	void render(SDL_Renderer* r, int offset_x, int offset_y, std::vector<IBlock*>* blocks);

	bool isBlocked(int x, int y);
	bool checkCollision(IBlock* block);

	void setBlock(int x, int y, int id);
	void joinBlock(IBlock* block);

	void findBlocksToRemove();
	SDL_Point removeNextBlock();
	void shiftBlocks();
	std::queue<SDL_Point> blocksToRemove;

	bool findEmptySpot(IBlock* block);

	int getWidth() { return w; };

protected:
	SDL_Texture* borderTexture;
	int level[20 * 10];

	int h = 20;
	int w = 10;

	int minRemoveY = 99;
	int linesToRemove = 0;

	


	
};