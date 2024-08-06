#include <SDL2/SDL.h>
#include "../../../renderer.h"
#include "Fade.h"

bool updateFade(Fade* fader) {
	if(fader->fade == 0){//Fade in
		if(fader->timer > 0){
			if(!((fader->timer - fader->amount) <= 0)){				
				fader->timer = fader->timer - fader->amount;
				return false;
			}else{
				fader->timer = 0;
				return true;
			}
		}
	}else{
		if(fader->timer < 255){
			if(!((fader->timer + fader->amount) >= 255)){
				fader->timer = fader->timer + fader->amount;
				return false;
			}else{
				fader->timer = 255;
				return true;
			}
		}
	}
	return false;
}

void drawFade(Fade* fader){
	SDL_Rect rect = {0,0,1280,720};
	SDL_SetRenderDrawColor(renderer,0,0,0,fader->timer);
	SDL_RenderFillRect(renderer, &rect);
}

