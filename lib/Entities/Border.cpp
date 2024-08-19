#include "Border.h"
#include "../../renderer.h"
#include "../Modules/Visuals/renderSprite.h"

void drawBorder(int x, int y, int w, int h, SDL_Texture* texture){
	int srcrect[] = {400,0,100,100};
	int dstrect[] = {x,y,w,h};
	renderSprite(srcrect, dstrect, texture);
}

