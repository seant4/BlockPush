#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "Entity.h"

struct Laser : public Entity{
	int x; //X pos
	int y; //Y pos
	int dist; //Width
	int width;
	int height;
	int orientation;
	bool update(std::vector<std::vector<int>> board);
	void draw(int x, int y);
};

void drawLaser(Laser *laser, int x, int y);
//bool updateLaser(Laser *laser, std::vector<std::vector<int>> board);
