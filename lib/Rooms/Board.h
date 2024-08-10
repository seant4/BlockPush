#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "../Entities/Player.h"
#include "../Entities/Block.h"
#include "../Entities/Wall.h"
#include "../Entities/WinBlock.h"
#include "../Entities/Border.h"
#include "../Entities/Laser.h"

struct Board {
	SDL_Texture* block_sheet;
	std::vector<std::vector<int>> board;
	std::vector<std::pair<int, int>> wincon;
	Laser* lasers;
	int nlasers;
	int width;
	int height;
	int scrollingOffset; //For scrolling background
}; 


void createBoard(Board* room, int width, int height, std::vector<std::vector<int>> temp);
int updateBoard(Board* room, int key);
void drawBoard(Board* room);
