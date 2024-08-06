#include "Player.h"
#include "../../renderer.h"


void drawPlayer(int x, int y, int w, int h){
	SDL_SetRenderDrawColor(renderer, 17, 173, 193, 255);
	SDL_Rect dstrect = {x,y,w,h};
	SDL_RenderFillRect(renderer, &dstrect);
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
