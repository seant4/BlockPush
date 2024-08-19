#include "Scientist.h"
#include "../../renderer.h"
#include "../Modules/Visuals/renderSprite.h"

void drawScientist(int x, int y, int w, int h, int off, int frame, SDL_Texture* t){
	int srcrect[] = {off * 100,(frame % 2) * 100,100,100};
	int dstrect[] = {x,y,w,h};
	renderSprite(srcrect, dstrect, t);
}
