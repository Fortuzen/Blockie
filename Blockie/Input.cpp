#pragma once
#include "Input.h"

void Input::init()
{
	m_quit = false;
}

void Input::update()
{
	keysDown.clear();
	keysUp.clear();

	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
		case SDL_QUIT:
			m_quit = true;
			break;
		case SDL_KEYDOWN:
			keys[e.key.keysym.sym] = true;
			keysDown[e.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			keys[e.key.keysym.sym] = false;
			keysUp[e.key.keysym.sym] = true;
			break;
		}
	}
}

bool Input::key(SDL_Keycode sym)
{
	if (keys[sym] != NULL) {
		return true;
	}
	return false;
}

bool Input::keyDown(SDL_Keycode sym)
{
	if (keysDown[sym] != NULL) {
		return true;
	}
	return false;
}

bool Input::keyUp(SDL_Keycode sym)
{
	if (keysUp[sym] != NULL) {
		return true;
	}
	return false;
}

bool Input::quit()
{
	return m_quit;
}
