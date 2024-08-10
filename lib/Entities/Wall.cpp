#include "Wall.h"
#include "../../renderer.h"

void drawWall(int x, int y, int w, int h, SDL_Texture* texture){
	SDL_Rect srcrect = {300,0,100,100};
	SDL_Rect dstrect = {x,y,w,h};
	SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
}

