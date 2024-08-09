#include "Block.h"
#include "Player.h"
#include "Wall.h"
#include <vector>
#include <math.h>
#include "../../renderer.h"
#include "../Modules/Physics/physics.h"
#include "../Modules/Visuals/createTexture.h"

void drawBlock(int x, int y, int w, int h, SDL_Texture* texture, std::vector<std::vector<int>> blocks){
	SDL_Rect srcrect = {100,0,100,100};
	SDL_Rect dstrect = {x,y,w,h};
	SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
	for(int i = 0; i < blocks.size(); i++){
		if(!(blocks[i][0] == x && blocks[i][1] == y)){
			int dist = sqrt( ((blocks[i][0] - x) * (blocks[i][0] - x)) + ((blocks[i][1] - y) * (blocks[i][1] - y)));
			if(dist == 50){
				SDL_Rect dstrect = {x,y,w,h};
				SDL_SetRenderDrawColor(renderer, 0,0,0,255);
				SDL_RenderFillRect(renderer, &dstrect);
			}
					
		}
	}
}

void updateBlock(Block* b){
}
