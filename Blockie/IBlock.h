#pragma once
#include <SDL.h>
#include "Game.h"

class IBlock {
public:
	virtual void init(SDL_Renderer* r) = 0;
	virtual void move(int x1, int y1);
	virtual void rotate();
	virtual void reset();
	virtual void render(SDL_Renderer* r, int offset_x, int offset_y);

	virtual int* getCurrentShape() { return shapes[currentShape]; };

	virtual int getXPos() { return pos_x; };
	virtual int getYPos() { return pos_y; };
	virtual int getId() { return id; };
	virtual SDL_Texture* getTexture() { return blockTexture; };
protected:
	int currentShape;
	int shapes[4][16];
	int id;
	int pos_x;
	int pos_y;

	SDL_Texture* blockTexture;
};