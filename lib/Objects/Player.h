#pragma once

struct Player{
	int x; //X pos
	int y; //Y pos
	int w; //Width
	int h; //Height	
};

void drawPlayer(int x, int y, int w, int h);
void updatePlayer(Player* p, int key);
