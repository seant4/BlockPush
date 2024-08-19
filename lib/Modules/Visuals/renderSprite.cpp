#include <SDL2/SDL.h>
#include "../../../renderer.h"
#include "renderSprite.h"

void renderSprite(int* srcPos, int* destPos, SDL_Texture* texture){
	SDL_Rect srcrect = {srcPos[0],srcPos[1],srcPos[2],srcPos[3]};
	SDL_Rect dstrect = {destPos[0],destPos[1],destPos[2],destPos[3]};
	SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
}

