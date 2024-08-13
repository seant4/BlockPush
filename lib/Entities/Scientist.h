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

	void draw();
};
