#pragma once
#include <SDL.h>

class ScrollingText {
public:
	ScrollingText() {};
	~ScrollingText() { SDL_DestroyTexture(textTexture); };

	void init(SDL_Renderer* r,const char* text, int sw, int sh, int x, int y, int v);
	void update(double deltatime);
	void render(SDL_Renderer* r);

	void changeText(SDL_Renderer* r, const char* text);

protected:
	int pos_x;
	int pos_y;
	int velocity;

	int screen_w;
	int screen_h;

	SDL_Texture* textTexture;
	int texture_w;
	int texture_h;
};