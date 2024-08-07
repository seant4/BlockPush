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
};

void drawBlock(int x, int y, int w, int h, SDL_Texture* texture);
void updateBlock(Block* b, int key);
