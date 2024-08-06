#pragma once
#include "Player.h"
#include "Wall.h"
#include <vector>

struct Block{
	int x; //X pos
	int y; //Y pos
	int w; //Width
	int h; //Height	
};

void drawBlock(int x, int y, int w, int h);
void updateBlock(Block* b, int key, Player* p, std::vector<Wall> walls);
