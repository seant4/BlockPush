#include "Block.h"
#include "Player.h"
#include "Wall.h"
#include <vector>
#include "../../renderer.h"
#include "../Modules/Physics/physics.h"

void drawBlock(int x, int y, int w, int h){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Rect dstrect = {x,y,w,h};
	SDL_RenderFillRect(renderer, &dstrect);
}

void updateBlock(Block* b, int key, Player* p, std::vector<Wall> walls){
	/*
	bool col = false;

	if(rectCollision(b->x+1, b->y, b->w, b->h, p->x, p->y, p->w, p->h) || 
		rectCollision(b->x-1, b->y, b->w, b->h, p->x, p->y, p->w, p->h)	||
		rectCollision(b->x, b->y+1, b->w, b->h, p->x, p->y, p->w, p->h) ||
		rectCollision(b->x, b->y-1, b->w, b->h, p->x, p->y, p->w, p->h)){
		col = true;
	}
	if(col){
		switch(key){
			case 1: //UP
				for(int i = 0; i < walls.size(); i++){
					if(!rectCollision(b->x, b->y-1, b->w, b->h, walls[i].x, walls[i].y, walls[i].w, walls[i].h)){
						b->y -= 100;
					}
				}
				break;
			case 2: //Down
				for(int i = 0; i < walls.size(); i++){
					if(!rectCollision(b->x, b->y+1, b->w, b->h, walls[i].x, walls[i].y, walls[i].w, walls[i].h)){
						b->y += 100;
					}
				}
				break;
			case 3: //Left
				for(int i = 0; i < walls.size(); i++){
					if(!rectCollision(b->x-1, b->y, b->w, b->h, walls[i].x, walls[i].y, walls[i].w, walls[i].h)){
						b->x -=100;
					}
				}
				break;
			case 4: //Right
				for(int i = 0; i < walls.size(); i++){
					if(!rectCollision(b->x+1, b->y, b->w, b->h, walls[i].x, walls[i].y, walls[i].w, walls[i].h)){
						b->x += 100;
					}
				}
				break;
		}
	}
	*/
}
