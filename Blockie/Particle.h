#pragma once
#include <SDL.h>

class Particle
{
public:
	Particle() {};
	~Particle() {};

	void init(int x, int y, int dir, int velocity, SDL_Texture* texture = NULL);
	void update(double deltatime);
	void render(SDL_Renderer* r);

	bool alive = true;
	double time;
protected:
	int pos_x;
	int pos_y;
	int dir;
	int velocity;

	SDL_Color color{ 0,255,0 };
	SDL_Texture* m_texture;
};

