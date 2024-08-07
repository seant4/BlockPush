#pragma once
#include <SDL2/SDL.h>

struct Border{
	int x; //X pos
	int y; //Y pos
	int w; //Width
	int h; //Height	
};

void drawBorder(int x, int y, int w, int h, SDL_Texture* texture);
