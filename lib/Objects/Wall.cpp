#include "Wall.h"
#include "../../renderer.h"
#include "../Modules/Physics/physics.h"

void drawWall(int x, int y, int w, int h){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Rect dstrect = {x,y,w,h};
	SDL_RenderFillRect(renderer, &dstrect);
}

void updateWall(Wall* w){

}
