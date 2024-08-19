#include "Wall.h"
#include "../../renderer.h"
#include "../Modules/Visuals/renderSprite.h"
void drawWall(int x, int y, int w, int h, SDL_Texture* texture){
	int srcPos[] = {300,0,100,100};
	int destPos[] = {x,y,w,h};
	renderSprite(srcPos, destPos, texture);
}

