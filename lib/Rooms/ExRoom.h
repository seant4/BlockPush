#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "../Objects/Player.h"
#include "../Objects/Block.h"
#include "../Objects/Wall.h"
#include "../Objects/WinBlock.h"
#include "../Objects/Border.h"

struct ExRoom {
    SDL_Texture* background;
	SDL_Texture* block_sheet;
	std::vector<std::vector<int>> board;
	std::vector<std::pair<int, int>> wincon;
	int width;
	int height;
	int scrollingOffset; //For scrolling background
}; 


void createExRoom(ExRoom* room, int width, int height, std::vector<std::vector<int>> temp);
int updateExRoom(ExRoom* room, int key);
void drawExRoom(ExRoom* room);
