#include "Scientist.h"
#include "../../renderer.h"
void Scientist::draw(){
	if(state == 4){
		state = 0;
	}

	SDL_Rect srcrect = {(state * 632),0,632,986};
	SDL_Rect dstrect = {x,y,w,h};
	SDL_RenderCopy(renderer, t, &srcrect, &dstrect);
	if(frame % 5 == 0){
		state++;
	}

	frame++;
}
