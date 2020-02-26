#pragma once
#include <vector>

#include "Game.h"
#include "Scene.h"
#include "ParticleManager.h"
#include "IBlock.h"
#include "Level.h"


class Scene_Game :
	public Scene
{
public:
	Scene_Game() {};
	~Scene_Game() {};

	void start();
	void update(double deltatime);
	void render();
	void close();

	IBlock* randomBlock();
protected:
	ParticleManager particleManager;
	Level level;
	IBlock* currentBlock;
	std::vector<IBlock*> blocks;

	PROCESSES currentProcess;

	double moveDownCooldown = 0.05;
	double actionCooldown = 0.05;

	double moveDownTimer = 1.0;
	double destroyTimer = 0.1;
};

