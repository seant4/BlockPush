#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include "Manager.h"
#include "../renderer.h"
#include "roomstate.h"

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
	std::vector<std::vector<int>> map;
	loadLevel(path, map);
	int width = map[0].size();
	int height = map.size();

	createBoard(&(manager->board),width, height, map);
}


/* Update loop (game logic loop)
 *
 * @param
 * Manager* manager: Room manager object
 * int key: User input key binding
 */
void updateManager(Manager* manager, int key){
	int state = updateBoard(&(manager->board), key);
	if(state == 2){
		manager->currentBoard = "./lib/Levels/lvl1.txt";
		loadBoard(manager, manager->currentBoard);
	}else if(state == 3){
		loadBoard(manager, manager->currentBoard);
	}

}

/* Manager create event
 *
 * @param
 * Manager* manager: Room manager object
 */
void createManager(Manager* manager){
	manager->currentBoard = "./lib/Levels/lvl2.txt";
	loadBoard(manager, manager->currentBoard);
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
}

