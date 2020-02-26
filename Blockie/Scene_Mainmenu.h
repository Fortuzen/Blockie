#pragma once
#include "Game.h"
#include "Scene.h"
#include "ScrollingText.h"

class Scene_Mainmenu :
	public Scene
{
public:
	Scene_Mainmenu() {};
	~Scene_Mainmenu() {};

	void start();
	void update(double deltatime);
	void render();
	void close();
protected:
	ScrollingText* scrollingText;
	Game* p_game;
};

