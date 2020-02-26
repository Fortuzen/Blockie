#pragma once
#include "ParticleMachine.h"
#include "ParticleManager.h"
#include <iostream>

void ParticleMachine::init(int x, int y) {
	pos_x = x; pos_y = y;
	alive = true;
	for (int i = 0; i < particleCount; i++) {
		particles[i] = new Particle();
		particles[i]->init(x,y,rand()%360,350 + rand()%100, ParticleManager::blocks[rand()%ParticleManager::blockCount]);		
	}
}

void ParticleMachine::update(double deltatime) {
	bool isDead = true;
	for (int i = 0; i < particleCount; i++) {
		if (particles[i]->alive) {
			particles[i]->update(deltatime);
			isDead = false;
		}
		else if(loop) {
			if (particles[i]->time <= 0.0) {
				particles[i]->init(pos_x, pos_y, rand() % 360, 350 + rand() % 100);
			}
		}
	}

	if (isDead) {
		alive = false;
	}
}

void ParticleMachine::render(SDL_Renderer* r) {
	for (int i = 0; i < particleCount; i++) {
		if (particles[i]->alive) {
			particles[i]->render(r);
		}
	}
}

void ParticleMachine::close() {
	for (int i = 0; i < particleCount; i++) {
		delete particles[i];
	}
}


