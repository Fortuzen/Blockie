#pragma once
#include <map>
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>


class Resources
{
public:
	Resources() {};
	~Resources() {};

	void init();
	void clear();
	SDL_Texture* getTexture(std::string name);
	SDL_Texture* getText(std::string name);
	Mix_Chunk* getSound(std::string name);
	Mix_Music* getMusic(std::string name);

protected:
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, SDL_Texture*> texts;
	std::map<std::string, Mix_Chunk*> sounds;
	std::map<std::string, Mix_Music*> music;
	

	void loadTextures();
	void loadTexts();
	void loadSounds();
	void loadMusic();

	void createText(std::string, const char* text);
};

