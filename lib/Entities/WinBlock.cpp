#include <SDL2/SDL.h>
#include "WinBlock.h"
#include "../Modules/Visuals/renderSprite.h"
#include "../../renderer.h"

void drawWinBlock(int x, int y, int w, int h, SDL_Texture* texture){
	int srcPos[] = {200,0,100,100};
	int destPos[] = {x,y,w,h};
	renderSprite(srcPos, destPos, texture);
}
