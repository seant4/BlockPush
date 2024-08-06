#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../../../renderer.h"


void dispText(int x, int y, int w, int h, char* t, TTF_Font* font){
	SDL_Color color = {0,0,0};
	SDL_Surface* text = TTF_RenderText_Solid(font, t, color);
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text);
	SDL_Rect dest = {0,0,text->w, text->h};
	SDL_RenderCopy(renderer, text_texture, NULL, &dest);
}
