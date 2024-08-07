#pragma once
#include <SDL2/SDL.h>

struct Wall{
	int x; //X pos
	int y; //Y pos
	int w; //Width
	int h; //Height	
	Wall(int xi, int yi, int wi, int hi):
		x(xi), y(yi), w(wi), h(hi){}
};


void drawWall(int x, int y, int w, int h, SDL_Texture* texture);
void updateWall(Wall* w);
