#pragma once
#include "IBlock.h"

class BLine : public IBlock {
public:
	BLine() {};
	~BLine() {};

	void init(SDL_Renderer* r);

};

void BLine::init(SDL_Renderer* r) {
	id = 1;
	pos_x = 4;
	pos_y = 0;
	currentShape = 0;
	int tempShape0[] = {
			1,1,1,1,
			0,0,0,0,		
			0,0,0,0,
			0,0,0,0
	};
	int tempShape1[] = {
			0,0,1,0,
			0,0,1,0,
			0,0,1,0,
			0,0,1,0
	};
	int tempShape2[] = {
			1,1,1,1,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0
	};
	int tempShape3[] = {
			0,0,1,0,
			0,0,1,0,
			0,0,1,0,
			0,0,1,0
	};

	memcpy(shapes[0], &tempShape0, sizeof(int) * 16);
	memcpy(shapes[1], &tempShape1, sizeof(int) * 16);
	memcpy(shapes[2], &tempShape2, sizeof(int) * 16);
	memcpy(shapes[3], &tempShape3, sizeof(int) * 16);

	blockTexture = Game::getInstance().resources.getTexture("turq");

}