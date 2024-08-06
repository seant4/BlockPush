#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "../Objects/Player.h"
#include "../Objects/Block.h"
#include "../Objects/Wall.h"
#include "../Objects/Grid.h"

struct ExRoom {
    SDL_Texture* background;
	int board[6][12];
	int width;
	int height;
}; 

void createExRoom(ExRoom* room);
void updateExRoom(ExRoom* room, int key);
void drawExRoom(ExRoom* room);
