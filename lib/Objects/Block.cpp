#include "Block.h"
#include "Player.h"
#include "Wall.h"
#include <vector>
#include "../../renderer.h"
#include "../Modules/Physics/physics.h"
#include "../Modules/Visuals/createTexture.h"

void drawBlock(int x, int y, int w, int h, SDL_Texture* texture){
	//SDL_SetRenderDrawColor(renderer, 96, 108, 129, 255);
	SDL_Rect srcrect = {100,0,100,100};
	SDL_Rect dstrect = {x,y,w,h};
	SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
}

void updateBlock(Block* b, int key){
}
