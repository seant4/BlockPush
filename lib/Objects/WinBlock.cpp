#include <SDL2/SDL.h>
#include "WinBlock.h"
#include "../../renderer.h"

void drawWinBlock(int x, int y, int w, int h, SDL_Texture* texture){
	SDL_Rect srcrect = {200,0,100,100};
	SDL_Rect dstrect = {x,y,w,h};
	SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
}
