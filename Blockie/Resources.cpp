#include "Resources.h"
#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>


#include <iostream>


void Resources::init() {
	loadTextures();
	loadTexts();
	loadSounds();
	loadMusic();
}

void Resources::clear()
{
	//Textures
	for (std::pair<std::string, SDL_Texture*> it : textures) {
		SDL_DestroyTexture(it.second);
	}
	textures.clear();
	//Texts
	for (std::pair<std::string, SDL_Texture*> it : texts) {
		SDL_DestroyTexture(it.second);
	}
	texts.clear();
	//Sounds
	for (std::pair<std::string, Mix_Chunk*> it : sounds) {
		Mix_FreeChunk(it.second);
	}
	sounds.clear();
	//Music
	for (std::pair<std::string, Mix_Music*> it : music) {
		Mix_FreeMusic(it.second);
	}
	music.clear();
	SDL_Log("Resources closed!");
}


void Resources::loadTextures()
{

	SDL_Renderer* r = Game::getInstance().renderer;

	textures["blue"] = IMG_LoadTexture(r, "blocks/blue.png");
	textures["green"] = IMG_LoadTexture(r, "blocks/green.png");
	textures["orange"] = IMG_LoadTexture(r, "blocks/orange.png");
	textures["purple"] = IMG_LoadTexture(r, "blocks/purple.png");
	textures["red"] = IMG_LoadTexture(r, "blocks/red.png");
	textures["turq"] = IMG_LoadTexture(r, "blocks/turq.png");
	textures["yellow"] = IMG_LoadTexture(r, "blocks/yellow.png");
	textures["gray"] = IMG_LoadTexture(r, "blocks/gray.png");

	textures["mainmenu"] = IMG_LoadTexture(r, "mainmenu.png");
}

//Hack remove this
void Resources::createText(std::string key, const char* text) {
	//
	SDL_Surface* surface_text = TTF_RenderText_Solid(Game::getInstance().font, text, SDL_Color{ 255,255,255 });
	SDL_Texture* text_TETRIS = SDL_CreateTextureFromSurface(Game::getInstance().renderer, surface_text);
	texts[key] = text_TETRIS;
	SDL_FreeSurface(surface_text);
};

void Resources::loadTexts() {

	createText("tetris", "BLOCKIE");
	createText("gameover", "GAMEOVER!");
	//createText("Mainmenu", "Mainmenu");
	createText("mainmenu_start", "Press Enter to start!");
	createText("hello", "Hello!");
	createText("highscore", "Highscore");
	createText("score", "Score");
	createText("level", "Level");
	createText("lines", "Lines");
	
}

void Resources::loadSounds()
{
	sounds["punch"] = Mix_LoadWAV("punch.ogg");

}

void Resources::loadMusic()
{
	music["music_1"] = Mix_LoadMUS("tetris.xm");
}

SDL_Texture * Resources::getTexture(std::string name)
{
	return textures[name];
}

SDL_Texture * Resources::getText(std::string name) {
	return texts[name];
}

Mix_Chunk * Resources::getSound(std::string name)
{
	return sounds[name];
}

Mix_Music * Resources::getMusic(std::string name)
{
	return music[name];
}
