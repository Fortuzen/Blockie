#pragma once
#include "Scene.h"
class Scene_Gameover :
	public Scene
{
public:
	Scene_Gameover() {};
	~Scene_Gameover() {};
	void start();
	void update(double deltatime);
	void render();
	void close();
};

