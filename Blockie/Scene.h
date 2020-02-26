#pragma once
#include <string>

class Scene
{
public:
	Scene() {};
	~Scene() {};

	virtual void start() = 0;
	virtual void update(double deltatime) = 0;
	virtual void render() = 0;
	virtual void close() = 0;

	std::string name;

};

