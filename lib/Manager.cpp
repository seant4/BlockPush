#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include "Manager.h"
#include "../renderer.h"
#include "roomstate.h"
#include "./Modules/Visuals/fade.h"
#include "./Modules/Visuals/renderSprite.h"
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
void loadBoard(Manager* manager, std::string path, int f){
	SDL_RenderClear(renderer);
	std::vector<std::vector<int>> map;
	loadLevel(path, map);
	int width = map[0].size();
	int height = map.size();
	manager->overworld.create();
	createBoard(&(manager->board),width, height, map, f);
	map.clear();
}

void changeBoard(Manager* manager, int b, int f){
	manager->fader = {255,6,0};
	manager->currentBoard = b;
	std::string path = "./lib/Levels/lvl" + std::to_string(b) + ".txt";
	loadBoard(manager, path, f);
}

/* Update loop (game logic loop)
 *
 * @param
 * Manager* manager: Room manager object
 * int key: User input key binding
 */
void updateManager(Manager* manager, int key){
	manager->fadeState = updateFade(&(manager->fader));
	int state = 0;
	if(!(manager->boardTrans)){
		state = updateBoard(&(manager->board), key);
	}
	if(state == 2 && manager->boardTrans == false){ //Start transition
		manager->boardTrans = true;

	}else if(state == 3){
		changeBoard(manager, manager->currentBoard, 2);
	}

	if(manager->boardTrans == true && manager->transState < 1920 && manager->transState >= 0){//During transition
		manager->transState += 9;
	}
	if(manager->transState >= 1920){	
		manager->fader = {0,6,1};
		manager->transState = -1;
	}
	if(manager->fadeState == true && manager->boardTrans == true){//End transition
		manager->currentBoard++;
		changeBoard(manager, manager->currentBoard, 2);
		manager->boardTrans = false;
		manager->transState = 0;
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
	changeBoard(manager, manager->currentBoard, 1);
	manager->boardTrans = false;
	manager->transState = 0;
}

/* Manager draw event
 *
 * @param
 * Manager* manager: Room manager object
 */
void drawManager(Manager* manager){
	if(roomState == 1){
		drawBoard(&(manager->board));
	}
	if(manager->boardTrans == true){
		int dest[] = {(-1920)+manager->transState,440,1920,200};
		if(manager->transState == -1){
			dest[0] = 0;
		}
		int rgb[] = {28,22,45};
		renderRect(dest, rgb, 255);
	}
	drawFade(&(manager->fader));	
}



#ifdef DEBUG
void debugManager(Manager* manager, std::string input){
	size_t openParen = input.find('(');
	size_t closeParen = input.find(')');
	if (openParen == std::string::npos || closeParen == std::string::npos || openParen >= closeParen) {
        throw std::invalid_argument("Invalid format: Missing or misplaced parentheses.");
    }
	std::string command = input.substr(0, openParen);
	std::string param = input.substr(openParen+1, closeParen - 1);
	int parami = stoi(param);
	if(command == "changeB"){
		manager->currentBoard = parami;
		changeBoard(manager, manager->currentBoard, 2);
	}
}
#endif
