#pragma once
#include <SDL2/SDL.h>

void renderSprite(int* srcPos, int* destPos, SDL_Texture* texture);
void renderRect(int* destPos, int* rgb, int alpha);
