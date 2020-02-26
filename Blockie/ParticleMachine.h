#pragma once
#include "Particle.h"
#include <SDL.h>

class ParticleMachine
{
public:
	ParticleMachine() {};
	~ParticleMachine() {};

	void init(int x, int y);
	void update(double deltatime);
	void render(SDL_Renderer* r);
	void close();

	bool alive = false;

protected:
	bool loop = false;


	int particleCount = 20;
	Particle* particles[20];
	int pos_x;
	int pos_y;
};

