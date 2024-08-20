#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "Entity.h"

struct Laser{
	Entity e;
	int dist; //Width
	int orientation;
	bool update(std::vector<std::vector<int>> board);
	void draw(int x, int y, SDL_Texture* t);
};

