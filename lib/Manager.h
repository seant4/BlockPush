#pragma once
#include <SDL2/SDL.h>
#include <vector>

#include "./Rooms/Board.h"
#include "./Modules/Visuals/fade.h"
#include "./Rooms/Overworld.h"
struct Manager{
	Board board;
	bool boardTrans;
	Fade fader;
	int currentBoard;
	int n;
	int fadeState;
	Overworld overworld;
};

void updateManager(Manager* manager, int key);
void createManager(Manager* manager);
void drawManager(Manager* manager);
