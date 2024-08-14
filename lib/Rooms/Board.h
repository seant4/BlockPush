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
#include "../Entities/Scientist.h"
struct Board {
	SDL_Texture* background;
	SDL_Texture* block_sheet;
	SDL_Texture* character;
	SDL_Texture* lab;
	int frame;
	std::vector<std::vector<int>> board;
	std::vector<std::pair<int, int>> wincon;
	Laser* lasers;
	int** blocks1;
	int** blocks2;
	int block1;
	int block2;
	int nlasers;
	int width;
	int height;
	int scrollingOffset; //For scrolling background
}; 


void createBoard(Board* room, int width, int height, std::vector<std::vector<int>> temp, int f);
int updateBoard(Board* room, int key);
void drawBoard(Board* room);
