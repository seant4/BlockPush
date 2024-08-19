#include "../Modules/Visuals/renderSprite.h"
#include "Player.h"
#include "../../renderer.h"


void drawPlayer(int x, int y, int w, int h, SDL_Texture* texture){
	int srcPos[] = {0,0,100,100};
	int destPos[] = {x,y,w,h};
	renderSprite(srcPos, destPos, texture);
}

