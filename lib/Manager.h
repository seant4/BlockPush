#pragma once
#include <SDL2/SDL.h>
#include <vector>

#include "./Rooms/Board.h"
#include "./Modules/Visuals/fade.h"
#include "./Rooms/Overworld.h"
struct Manager{
	Board board;
	bool boardTrans;
	bool fadeState;
	int transState;
	Fade fader;
	int currentBoard;
	int n;
	Overworld overworld;
};

void updateManager(Manager* manager, int key);
void createManager(Manager* manager);
void drawManager(Manager* manager);
#ifdef DEBUG
void debugManager(Manager* manager, std::string input);
#endif
