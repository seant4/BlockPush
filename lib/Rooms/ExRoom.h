#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "../Objects/Player.h"
#include "../Objects/Block.h"
#include "../Objects/Wall.h"

struct ExRoom {
    SDL_Texture* background;
	std::vector<std::vector<int>> board;
	int width;
	int height;
}; 


void createExRoom(ExRoom* room, int width, int height, std::vector<std::vector<int>> temp);
void updateExRoom(ExRoom* room, int key);
void drawExRoom(ExRoom* room);
