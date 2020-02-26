#pragma once
#include <iostream>
#include "IBlock.h"

void IBlock::move(int x1, int y1) {
	pos_x += x1;
	pos_y += y1;
}

void IBlock::rotate() {
	currentShape += 1;
	if (currentShape > 3) {
		currentShape = 0;
	}
}

void IBlock::reset() {
	pos_x = 4;
	pos_y = 0;
	currentShape = 0;
}
void IBlock::render(SDL_Renderer* r, int offset_x, int offset_y) {
	SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
	SDL_Rect rect;
	rect.w = 32;
	rect.h = 32;


	int* temp = shapes[currentShape];
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			int i = y * 4 + x;

			if (temp[i] != 1) continue;

			rect.x = (pos_x + x) * 32 + offset_x;
			rect.y = (pos_y + y) * 32 + offset_y;

			if (blockTexture != NULL) {
				SDL_RenderCopy(r, blockTexture, NULL, &rect);
			}
			else {
				SDL_RenderFillRect(r, &rect);
			}
			

		}
	}

}
