#pragma once
#include <SDL2/SDL.h>

struct Scientist{
	int x;
	int y;
	int w;
	int h;
	SDL_Texture* t;
	int state;
	int frame;
};

void drawScientist(int x, int y, int w, int h, int off, int frame, SDL_Texture* t);
