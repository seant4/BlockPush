#pragma once
#include <SDL2/SDL.h>

struct Player{
	int x; //X pos
	int y; //Y pos
	int w; //Width
	int h; //Height	
};

void drawPlayer(int x, int y, int w, int h, SDL_Texture* texture);
void updatePlayer(Player* p, int key);
