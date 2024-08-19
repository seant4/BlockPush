#include <SDL2/SDL.h>
#include "../../../renderer.h"
#include "renderSprite.h"

void renderSprite(int* srcPos, int* destPos, SDL_Texture* texture){
	SDL_Rect dstrect = {destPos[0],destPos[1],destPos[2],destPos[3]};
	if(srcPos == NULL){	
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	}else{
		SDL_Rect srcrect = {srcPos[0],srcPos[1],srcPos[2],srcPos[3]};
		SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
	}
}

void renderRect(int* destPos, int* rgb, int alpha){
	SDL_Rect dstrect = {destPos[0],destPos[1],destPos[2],destPos[3]};
	SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], alpha);
	SDL_RenderFillRect(renderer, &dstrect);
}


