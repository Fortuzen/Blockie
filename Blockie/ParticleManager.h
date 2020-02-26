#pragma once
#include "ParticleMachine.h"

class ParticleManager
{
public:
	ParticleManager() {};
	~ParticleManager() {};

	void init(SDL_Renderer* r);
	void update(double deltatime);
	void render(SDL_Renderer* r);
	void close();

	void createMachineAt(int x, int y);

	static SDL_Texture* blocks[7];
	static int blockCount;
protected:
	int count = 20;
	ParticleMachine machines[20];


};

