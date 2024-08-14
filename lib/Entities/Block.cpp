#include "Block.h"
#include <vector>
#include <math.h>
#include "../../renderer.h"
#include "../Modules/Visuals/createTexture.h"

void drawBlock(int x, int y, int w, int h, SDL_Texture* texture, int** blocks, int n, int type){
	SDL_Rect srcrect = {0,0,100,100};
	if(type == 1){
		srcrect.x = 100;
	}else if(type == 8){
		srcrect.x = 500;
	}
	SDL_Rect dstrect = {x,y,w,h};
	SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
	for(int i = 0; i < n; i++){
		if(!(blocks[i][0] == x && blocks[i][1] == y)){
			int dist = sqrt( ((blocks[i][0] - x) * (blocks[i][0] - x)) + ((blocks[i][1] - y) * (blocks[i][1] - y)));
			if(dist == 100){
				SDL_Rect dstrect = {x,y,w,h};
				SDL_SetRenderDrawColor(renderer, 0,0,0,150);
				SDL_RenderFillRect(renderer, &dstrect);
				break;
			}
					
		}
	}
}
