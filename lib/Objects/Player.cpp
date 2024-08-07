#include "Player.h"
#include "../../renderer.h"


void drawPlayer(int x, int y, int w, int h, SDL_Texture* texture){
	SDL_Rect srcrect = {0,0,100,100};
	SDL_Rect dstrect = {x,y,w,h};
	SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
}

void updatePlayer(Player* p, int key){
	/*
	switch(key){
		case 1: //UP
			p->y -= 100;
			break;
		case 2: //Down
			p->y += 100;
			break;
		case 3: //Left
			p->x -=100;
			break;
		case 4: //Right
			p->x += 100;
			break;
	}
	*/
}
