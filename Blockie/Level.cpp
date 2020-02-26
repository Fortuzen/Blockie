#pragma once
#include "Level.h"
#include <SDL_image.h>

void Level::init(SDL_Renderer* r) {
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			level[y*w + x] = 0;
		}
	}

	borderTexture = IMG_LoadTexture(r, "blocks/gray.png");
}

bool Level::isBlocked(int x, int y) {
	if (x<0 || x>=w || y < 0 || y >= h) {
		return true;
	}

	int block = level[y*w+x];
	if (block != 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Level::checkCollision(IBlock* block) {
	int* shape = block->getCurrentShape();
	int xpos = block->getXPos();
	int ypos = block->getYPos();

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			int i = y * 4 + x;
			if (shape[i] < 1 || shape[i] > 7) continue;

			int xx = xpos + x;
			int yy = ypos + y;

			if (isBlocked(xx, yy)) {
				return true;
			}
		}
	}
	return false;
}

void Level::setBlock(int x, int y, int id) {
	level[y*w+x] = id;
}

void Level::joinBlock(IBlock* block) {
	int* shape = block->getCurrentShape();
	int xpos = block->getXPos();
	int ypos = block->getYPos();

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			int i = y * 4 + x;
			if (shape[i] < 1 || shape[i] > 7) continue;

			int xx = xpos + x;
			int yy = ypos + y;
			setBlock(xx, yy, block->getId());
		}
	}
}

void Level::findBlocksToRemove() {
	minRemoveY = 99;
	linesToRemove = 0;
	for (int y = 0; y < h; y++) {
		bool rr = true;
		for (int x = 0; x < w; x++) {
			int t = level[y*w + x];
			if (t == 0) {
				rr = false;
			}
		}
		if (rr) {
			for (int x = 0; x < w; x++) {
				blocksToRemove.push(SDL_Point{ x,y });
			}
			if (y < minRemoveY) minRemoveY = y;

			linesToRemove++;
		}
	}

	// Shift, another way, shit
	/*
	if (linesToRemove.size() > 0) {
		for (int y = h - 1 - 1; y > 0; y--) {
			for (int x = 1; x < w - 1; x++) {
				if (level[y*w + x] != 1) continue;

				int i = 1;
				while (!isBlocked(x, y + i)) {
					i++;
				}
				level[(y + i-1)*w + x] = 1;
				level[(y)*w + x] = 0;
			}
		}
	} */
}

SDL_Point Level::removeNextBlock() {
	// Remove
	SDL_Point p = blocksToRemove.front();
	blocksToRemove.pop();
	//std::cout << p.x << " " << p.y << "\n";
	level[p.y*w + p.x] = 0;

	return p;
}

void Level::shiftBlocks() {
	// Shift
	//std::cout << minRemoveY << "\n";
	if (linesToRemove > 0) {
		for (int y = minRemoveY-1; y >= 0; y--) {
			for (int x = 0; x < w; x++) {
				if (level[y*w + x] < 1 || level[y*w + x] > 7) continue;
				int temp = level[y*w + x];
				level[y*w + x] = 0;
				level[(y + linesToRemove)*w + x] = temp;
			}
		}
	}
}

bool Level::findEmptySpot(IBlock* block) {
	return false;
}

void Level::render(SDL_Renderer* r, int offset_x, int offset_y, std::vector<IBlock*>* blocks) {
	// Draw grid
	SDL_SetRenderDrawColor(r, 128, 128, 128, 255);

	for (int i = 0; i < h; i++) {
		SDL_Point p1;
		SDL_Point p2;
		p1.y = 32 + 32 * i;
		p1.x = 0;
		p2.y = 32 + 32 * i;
		p2.x = 32*w;
		SDL_RenderDrawLine(r, p1.x+offset_x, p1.y + offset_y, p2.x + offset_x,p2.y + offset_y);
	}
	for (int i = 0; i < w; i++) {
		SDL_Point p1;
		SDL_Point p2;
		p1.x = 32 + 32 * i;
		p1.y = 0;
		p2.x = 32 + 32 * i;
		p2.y = 32 * h;
		SDL_RenderDrawLine(r, p1.x + offset_x, p1.y + offset_y, p2.x + offset_x, p2.y + offset_y);
	}


	// Draw blocks
	SDL_SetRenderDrawColor(r, 255, 0, 0, 255);

	SDL_Rect rect;
	rect.h = 32;
	rect.w = 32;

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int id = -1;
			if (level[y*w + x] >= 1 && level[y*w + x] <= 7) {
				//SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
				id = level[y*w + x];
			}
			else {
				continue;
			}

			rect.y = 32 * y + offset_y;
			rect.x = 32 * x + offset_x;
			//SDL_RenderFillRect(r, &rect);
			SDL_RenderCopy(r, blocks->at(id-1)->getTexture(), NULL, &rect);
		}
	}

	// Draw borders

	SDL_SetRenderDrawColor(r, 128, 128, 128, 255);
	for (int y = 0; y < h; y++) {
		rect.y = 32 * y + offset_y;
		rect.x = -32 + offset_x;
		//SDL_RenderFillRect(r, &rect);
		SDL_RenderCopy(r, borderTexture, NULL, &rect);
		rect.x = 32*(w) + offset_x;
		//SDL_RenderFillRect(r, &rect);
		SDL_RenderCopy(r, borderTexture, NULL, &rect);
	}
	for (int x = -1; x < w+1; x++) {
		rect.x = 32 * x + offset_x;
		rect.y = -32 + offset_y;
		//SDL_RenderFillRect(r, &rect);
		SDL_RenderCopy(r, borderTexture, NULL, &rect);
		rect.y = 32 * (h)+offset_y;
		//SDL_RenderFillRect(r, &rect);
		SDL_RenderCopy(r, borderTexture, NULL, &rect);
	}
}