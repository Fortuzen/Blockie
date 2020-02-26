#pragma once
#include "IBlock.h"

class Block_S : public IBlock {
public:
	Block_S() {};
	~Block_S() {};

	void init(SDL_Renderer* r);

};

void Block_S::init(SDL_Renderer* r) {
	id = 5;
	pos_x = 4;
	pos_y = 0;
	currentShape = 0;
	int tempShape0[] = {
			0,0,1,1,
			0,1,1,0,
			0,0,0,0,
			0,0,0,0
	};
	int tempShape1[] = {
			0,0,1,0,
			0,0,1,1,
			0,0,0,1,
			0,0,0,0
	};
	int tempShape2[] = {
			0,0,1,1,
			0,1,1,0,
			0,0,0,0,
			0,0,0,0
	};
	int tempShape3[] = {
			0,0,1,0,
			0,0,1,1,
			0,0,0,1,
			0,0,0,0
	};

	memcpy(shapes[0], &tempShape0, sizeof(int) * 16);
	memcpy(shapes[1], &tempShape1, sizeof(int) * 16);
	memcpy(shapes[2], &tempShape2, sizeof(int) * 16);
	memcpy(shapes[3], &tempShape3, sizeof(int) * 16);
	blockTexture = Game::getInstance().resources.getTexture("green");
}


