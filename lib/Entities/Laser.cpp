#include "Laser.h"
#include "../../renderer.h"
#include "../Modules/Visuals/renderSprite.h"
#include <SDL2/SDL.h>

void Laser::draw(int x, int y, SDL_Texture* t){
	SDL_SetRenderDrawColor(renderer, 255,115,115,150);
	int srcrect[4];
	SDL_Rect dstrect;
	if(orientation == 0){ //Vertial	
		dstrect = {x,(y + 100),100,e.h};
		srcrect[0] = (7*100);
		srcrect[1] = 0;
		srcrect[2] = 100;
		srcrect[3] = 100;
	}else{ //Horizontal
		dstrect = {(x + 100), y,e.w, 100};	
		srcrect[0] = (8*100);
		srcrect[1] = 0;
		srcrect[2] = 100;
		srcrect[3] = 100;
	}
	int dstrect2[] = {x,y, 100,100};

	SDL_RenderFillRect(renderer, &dstrect);
	renderSprite(srcrect, dstrect2, t);

}

bool Laser::update(std::vector<std::vector<int>> board){
	if(orientation == 0){
		for(int i = e.y; i < board.size(); i++){
			if(board[i][e.x] == 2){
				return true;
			}
			if(board[i][e.x] == 1 || board[i][e.x] == 5 || board[i][e.x] == 3){
				e.h = (((i-(e.y))*100));
				break;
			}
		}
	}else{
		for(int i = e.x; i < board[0].size(); i++){
			if(board[e.y][i] == 2){
				return true;
			}
			if(board[e.y][i] == 1 || board[e.y][i] == 5 || board[e.y][i] == 3){
				e.w = (((i-(e.x))*100));
				break;
			}
		}
	}
	return false;
}
