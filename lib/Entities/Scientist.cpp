#include "Scientist.h"
#include "../../renderer.h"
void Scientist::draw(){
	if(state == 2){
		state = 0;
	}

	SDL_Rect srcrect = {(state * 632),0,632,986};
	SDL_Rect dstrect = {x,y,w,h};
	SDL_RenderCopy(renderer, t, &srcrect, &dstrect);
	if(frame % 10 == 0){
		state++;
	}

	frame++;
}

void drawScientist(int x, int y, int w, int h, int off, int frame, SDL_Texture* t){
	SDL_Rect srcrect = {off * 100,(frame % 2) * 100,100,100};
	SDL_Rect dstrect = {x,y,w,h};
	SDL_RenderCopy(renderer, t, &srcrect, &dstrect);

}
