#pragma once
#include <SDL2/SDL.h>
#include <vector>

struct Laser{
	int x; //X pos
	int y; //Y pos
	int dist; //Width
	int width;
	int height;
	int orientation;
};

void drawLaser(Laser *laser, int x, int y);
bool updateLaser(Laser *laser, std::vector<std::vector<int>> board);
