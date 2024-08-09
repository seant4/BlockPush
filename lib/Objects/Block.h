#pragma once
#include "Player.h"
#include "Wall.h"
#include <vector>
#include <SDL2/SDL.h>

struct Block{
	int x; //X pos
	int y; //Y pos
	int w; //Width
	int h; //Height	
	int cols; //Collisions
};

void drawBlock(int x, int y, int w, int h, SDL_Texture* texture, std::vector<std::vector<int>> blocks);
void updateBlock(Block* b);
