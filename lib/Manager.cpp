#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include "Manager.h"
#include "../renderer.h"
#include "roomstate.h"

#include "./Rooms/ExRoom.h"

void loadLevel(std::string dir, std::vector<std::vector<int>>& temp){
	std::ifstream in;
	in.open(dir);
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
//TODO: Custom path
void loadRoom(Manager* manager, std::string path){
	std::vector<std::vector<int>> map;
	loadLevel(path, map);
	int width = map[0].size();
	int height = map.size();

	createExRoom(&(manager->exroom),width, height, map);
}

void updateManager(Manager* manager, int key){
	int state = updateExRoom(&(manager->exroom), key);
	if(state == 2){
		loadRoom(manager, "./lib/Levels/lvl1.txt");
	}else if(state == 3){
		loadRoom(manager, "./lib/Levels/lvl2.txt");
	}

}

void createManager(Manager* manager){
	loadRoom(manager, "./lib/Levels/lvl2.txt");
}

void drawManager(Manager* manager){
	if(roomState == 1){
		drawExRoom(&(manager->exroom));
	}else{
	}
}

