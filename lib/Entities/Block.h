#pragma once
#include "Wall.h"
#include <vector>
#include <SDL2/SDL.h>

void drawBlock(int x, int y, int w, int h, SDL_Texture* texture, int** blocks, int n,int type);
