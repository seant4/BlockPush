#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include "Manager.h"
#include "../renderer.h"
#include "roomstate.h"
#include "./Modules/Visuals/fade.h"
#include "./Rooms/Board.h"


/* Loads level from .txt file
 *
 * @param
 * std::string path: Path to level file
 * std::vector<std::vector<int>>& temp: vector matrix to apply level too
 */
void loadLevel(std::string path, std::vector<std::vector<int>>& temp){
	std::ifstream in;
	in.open(path);
	std::string line;
	int i = 0;
	while(getline(in, line)){
		std::vector<int> l;
		for(char c: line){
			if(!(c == '{' || c == ' ' || c == ',' || c == '}')){
				int num = (int)c - 48;
				l.push_back(num);
			}
		}
		temp.push_back(l);
		l.clear();
	}
	in.close();
}


/* Instantiates a board
 *
 * @param
 * Manager* manager: Room manager object
 * std::string path: Path to level file
 */
void loadBoard(Manager* manager, std::string path){
	SDL_RenderClear(renderer);
	std::vector<std::vector<int>> map;
	loadLevel(path, map);
	int width = map[0].size();
	int height = map.size();
	manager->overworld.create();
	createBoard(&(manager->board),width, height, map);
}

void changeBoard(Manager* manager, int b){
	manager->fader = {255,6,0};
	manager->currentBoard = b;
	std::string path = "./lib/Levels/lvl" + std::to_string(b) + ".txt";
	loadBoard(manager, path);
}

/* Update loop (game logic loop)
 *
 * @param
 * Manager* manager: Room manager object
 * int key: User input key binding
 */
void updateManager(Manager* manager, int key){
	bool fadeState = updateFade(&(manager->fader));
	int state = 0;
	if(!(manager->boardTrans)){
		state = updateBoard(&(manager->board), key);
	}
	if(state == 2 && manager->boardTrans == false){
		manager->boardTrans = true;
		manager->fader = {0,6,1};

	}else if(state == 3){
		changeBoard(manager, manager->currentBoard);
	}
	if(fadeState == true && manager->boardTrans == true){
		manager->currentBoard++;
		changeBoard(manager, manager->currentBoard);
		manager->boardTrans = false;
	}

}

/* Manager create event
 *
 * @param
 * Manager* manager: Room manager object
 */
void createManager(Manager* manager){
	manager->fader = {255,6,0};
	manager->currentBoard = 1;
	changeBoard(manager, manager->currentBoard);
	manager->boardTrans = false;
}

/* Manager draw event
 *
 * @param
 * Manager* manager: Room manager object
 */
void drawManager(Manager* manager){
	if(roomState == 1){
		drawBoard(&(manager->board));
	}else{
	}
	drawFade(&(manager->fader));	
}

