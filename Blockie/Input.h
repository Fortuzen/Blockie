#pragma once
#include <SDL.h>
#include <map>

class Input
{
public:
	Input() {};
	~Input() {};
	void init();
	void update();

	bool key(SDL_Keycode sym);
	bool keyDown(SDL_Keycode sym);
	bool keyUp(SDL_Keycode sym);
	bool quit();

protected:
	std::map< SDL_Keycode, bool> keys;
	std::map< SDL_Keycode, bool> keysDown;
	std::map< SDL_Keycode, bool> keysUp;
	bool m_quit;
};

