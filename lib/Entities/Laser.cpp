#include "Laser.h"
#include "../../renderer.h"
#include <SDL2/SDL.h>

void Laser::draw(int x, int y, SDL_Texture* t){
	SDL_SetRenderDrawColor(renderer, 0,0,0,150);
	SDL_Rect srcrect;
	SDL_Rect dstrect;
	SDL_Rect dstrect2;
	if(orientation == 0){ //Vertial	
		dstrect = {x,(y + 100),100,h};
		srcrect = {(7 * 100), 0, 100, 100};
	}else{ //Horizontal
		dstrect = {(x + 100), y,w, 100};	
		srcrect = {(8 * 100), 0, 100, 100};
	}
	dstrect2 = {x,y, 100,100};
	SDL_RenderFillRect(renderer, &dstrect);
	SDL_RenderCopy(renderer, t, &srcrect, &dstrect2);

}

bool Laser::update(std::vector<std::vector<int>> board){
	if(orientation == 0){
		for(int i = y; i < board.size(); i++){
			if(board[i][x] == 2){
				return true;
			}
			if(board[i][x] == 1 || board[i][x] == 5 || board[i][x] == 3){
				h = (((i-y)*100));
				break;
			}
		}
	}else{
		for(int i = x; i < board[0].size(); i++){
			if(board[y][i] == 2){
				return true;
			}
			if(board[y][i] == 1 || board[y][i] == 5 || board[y][i] == 3){
				w = (((i-x)*100));
				break;
			}
		}
	}
	return false;
}
