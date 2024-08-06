#include <SDL2/SDL.h>
#include "../../../renderer.h"

SDL_Texture* createTexture(char* p){
    SDL_Surface* image = SDL_LoadBMP(p);
	if(image == NULL){
		printf("Image could not be loaded: %s\n", SDL_GetError());
	}
	SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, image);
	if(t == NULL){
		printf("Texture could not be created: %s\n", SDL_GetError());
	}
	SDL_FreeSurface(image);
	return t;
}
