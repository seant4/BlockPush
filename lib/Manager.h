#pragma once
#include <SDL2/SDL.h>
#include <vector>

#include "./Rooms/ExRoom.h"

struct Manager{
	ExRoom exroom;
	std::string currentBoard;
	int n;
};

void updateManager(Manager* manager, int key);
void createManager(Manager* manager);
void drawManager(Manager* manager);
