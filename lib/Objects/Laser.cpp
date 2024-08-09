#include "Laser.h"
#include "../../renderer.h"
#include <SDL2/SDL.h>

void drawLaser(Laser *laser, int x, int y){
	//SDL_Rect srcrect = {0,0,100,100};
	SDL_SetRenderDrawColor(renderer, 50,50,50,255);
	SDL_Rect dstrect;
	if(laser->orientation == 0){ //Vertial	
		dstrect = {x,y,50,laser->height};
	}else{ //Horizontal
		dstrect = {x, y, laser->width, 50};	
	}
	SDL_RenderFillRect(renderer, &dstrect);
	//SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
}
void updateLaser(Laser *laser, std::vector<std::vector<int>> board){
	if(laser->orientation == 0){
		for(int i = 0; i < board.size(); i++){
			if(board[i][laser->x] == 1 || board[i][laser->x] == 5 || board[i][laser->x] == 3){
				laser->height = (i * 50) - 1;
				break;
			}
		}
	}else{
		for(int i = 0; i < board[0].size(); i++){
			if(board[laser->y][i] == 1 || board[laser->y][i] == 5 || board[laser->y][i] == 3){
				laser->width = (i * 50) - 1;
				break;
			}
		}
	}

}
