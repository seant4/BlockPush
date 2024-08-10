#include "Laser.h"
#include "../../renderer.h"
#include <SDL2/SDL.h>

void Laser::draw(int x, int y){
	SDL_SetRenderDrawColor(renderer, 50,50,50,255);
	SDL_Rect dstrect;
	if(orientation == 0){ //Vertial	
		dstrect = {x,y,50,h};
	}else{ //Horizontal
		dstrect = {x, y,w, 50};	
	}
	SDL_RenderFillRect(renderer, &dstrect);
}

bool Laser::update(std::vector<std::vector<int>> board){
	if(orientation == 0){
		for(int i = 0; i < board.size(); i++){
			if(board[i][x] == 2){
				return true;
			}
			if(board[i][x] == 1 || board[i][x] == 5 || board[i][x] == 3){
				h= (i * 50) - 1;
				break;
			}
		}
	}else{
		for(int i = 0; i < board[0].size(); i++){
			if(board[y][i] == 2){
				return true;
			}
			if(board[y][i] == 1 || board[y][i] == 5 || board[y][i] == 3){
				w= (i * 50) - 1;
				break;
			}
		}
	}
	return false;
}
