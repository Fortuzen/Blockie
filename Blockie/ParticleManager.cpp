#pragma once
#include "ParticleManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Resources.h"
#include "Game.h"

SDL_Texture* ParticleManager::blocks[7];
int ParticleManager::blockCount;

void ParticleManager::init(SDL_Renderer* r)
{
	Game game = Game::getInstance();
	blocks[0] = game.resources.getTexture("blue");
	blocks[1] = game.resources.getTexture("green");
	blocks[2] = game.resources.getTexture("orange");
	blocks[3] = game.resources.getTexture("purple");
	blocks[4] = game.resources.getTexture("red");
	blocks[5] = game.resources.getTexture("turq");
	blocks[6] = game.resources.getTexture("yellow");
	blockCount = 7;

	for (int i = 0; i < count; i++) {
		machines[i].init(1000, 1000);
	}

}

void ParticleManager::update(double deltatime)
{
	for (int i = 0; i < count; i++) {
		if (machines[i].alive) {
			machines[i].update(deltatime);
		}
	}
}

void ParticleManager::render(SDL_Renderer * r)
{
	for (int i = 0; i < count; i++) {
		if (machines[i].alive) {
			machines[i].render(r);
		}
	}
}

void ParticleManager::createMachineAt(int x, int y)
{
	for (int i = 0; i < count; i++) {
		if( !machines[i].alive) {
			machines[i].init(x, y);
			break;
		}
	}
}

void ParticleManager::close() {
	for (int i = 0; i < count; i++) {
		machines[i].close();
	}
}
