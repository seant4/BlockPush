#pragma once
#include <SDL2/SDL.h>
#include <vector>

#include "./Rooms/Board.h"

struct Manager{
	Board board;
	std::string currentBoard;
	int n;
};

void updateManager(Manager* manager, int key);
void createManager(Manager* manager);
void drawManager(Manager* manager);
