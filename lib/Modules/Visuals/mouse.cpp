#include <SDL2/SDL.h>
#include <vector>
#include "../../../renderer.h"

std::vector<int> getMousePos(){
	int x;
	int y;
	int windowHeight=0;
	int windowWidth=0;
	int state = SDL_GetMouseState(&x, &y);
	SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);
	int xscaled = (float(x)/windowWidth)*1280;
	int yscaled = (float(y)/windowHeight)*720;
	return std::vector<int>{xscaled,yscaled,state};
}
