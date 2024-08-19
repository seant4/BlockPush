#include "Block.h"
#include <vector>
#include <math.h>
#include "../../renderer.h"
#include "../Modules/Visuals/createTexture.h"
#include "../Modules/Visuals/renderSprite.h"

void drawBlock(int x, int y, int w, int h, SDL_Texture* texture, int** blocks, int n, int type){
	int srcrect[] = {0,0,100,100};
	if(type == 1){
		srcrect[0] = 100;
	}else if(type == 8){
		srcrect[0] = 500;
	}
	int dstrect[] = {x,y,w,h};
	renderSprite(srcrect, dstrect, texture);
	for(int i = 0; i < n; i++){
		if(!(blocks[i][0] == x && blocks[i][1] == y)){
			int dist = sqrt( ((blocks[i][0] - x) * (blocks[i][0] - x)) + ((blocks[i][1] - y) * (blocks[i][1] - y)));
			if(dist == 100){
				int dstrect[] = {x,y,w,h};
				int rgb[] = {0,0,0};
				renderRect(dstrect, rgb, 150);
				break;
			}
					
		}
	}
}
