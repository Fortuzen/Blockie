#pragma once
#include "Particle.h"

void Particle::init(int x, int y, int ndir, int nvelocity, SDL_Texture* texture) {
	pos_x = x; pos_y = y; dir = ndir; velocity = nvelocity;
	time = 0.5;
	alive = true;

	if (texture) {
		m_texture = texture;
	}
}

void Particle::update(double deltatime) {
	double radians = (M_PI / 180.0) * dir;
	double vel = double(velocity);
	pos_x += (int)(vel*deltatime*cos(radians));
	pos_y += (int)(vel*deltatime*sin(radians));

	time -= deltatime;
	if (time <= 0) {
		alive = false;
	}
}

void Particle::render(SDL_Renderer* r) {
	SDL_Rect rect;
	rect.x = pos_x; rect.y = pos_y;
	rect.h = 8; rect.w = 8;
	if (m_texture) {
		SDL_RenderCopy(r, m_texture, NULL, &rect);
		return;
	}

	SDL_SetRenderDrawColor(r, 0, 255, 0, 255);
	SDL_RenderFillRect(r, &rect);
}


