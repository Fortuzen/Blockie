#pragma once
#include "ScrollingText.h"
#include "Game.h"
#include <SDL_ttf.h>
#include <iostream>

void ScrollingText::init(SDL_Renderer* r, const char* text, int sw, int sh, int x, int y, int v) {
	TTF_Font* font = TTF_OpenFont("m5x7.ttf", 64);
	SDL_Surface* surface_text = TTF_RenderText_Solid(font, text, SDL_Color{ 255,255,255 });
	textTexture = SDL_CreateTextureFromSurface(r, surface_text);
	texture_h = surface_text->h;
	texture_w = surface_text->w;
	SDL_FreeSurface(surface_text);
	TTF_CloseFont(font);

	pos_x = x;
	pos_y = y;
	velocity = v;

	screen_h = sh;
	screen_w = sw;
}

void ScrollingText::changeText(SDL_Renderer* r, const char* text) {
	TTF_Font* font = TTF_OpenFont("m5x7.ttf", 64);
	SDL_Surface* surface_text = TTF_RenderText_Solid(font, text, SDL_Color{ 255,255,255 });
	textTexture = SDL_CreateTextureFromSurface(r, surface_text);
	texture_h = surface_text->h;
	texture_w = surface_text->w;
	SDL_FreeSurface(surface_text);
	TTF_CloseFont(font);
}

void ScrollingText::update(double deltatime) {
	pos_x += (int)((double)velocity * deltatime);
	//std::cout << pos_x << "\n";
	pos_x = pos_x % (screen_w);

	/*
	if (pos_x <= -texture_w) {
		pos_x = screen_w - texture_w ;
	}
	else if (pos_x >= screen_w + texture_w) {
		pos_x = texture_w;
	}
	*/
}

void ScrollingText::render(SDL_Renderer* r) {
	SDL_Rect d;
	d.h = texture_h; d.w = texture_w; d.x = pos_x; d.y = pos_y;
	// This looks ugly but it works
	
	//Render once if fits screen
	if (pos_x >= 0 && pos_x + texture_w < screen_w) {
		SDL_RenderCopy(r, textTexture, NULL, &d);
	}
	else if (pos_x < 0) { // Render twice if does not fit
		int splitting_x = screen_w+pos_x;
		//std::cout << "x split: " << splitting_x << "\n";
		//Left "part"
		SDL_RenderCopy(r, textTexture, NULL, &d);
		//Right part
		d.x = splitting_x;
		SDL_RenderCopy(r, textTexture, NULL, &d);
	}
	else if (pos_x + texture_w >= screen_w) {
		int splitting_x = -1*(screen_w - pos_x);

		SDL_RenderCopy(r, textTexture, NULL, &d);

		d.x = splitting_x;
		SDL_RenderCopy(r, textTexture, NULL, &d);
	}



}