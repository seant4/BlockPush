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

void updateManager(Manager* manager, int key){
	updateExRoom(&(manager->exroom), key);
}

void createManager(Manager* manager){
	std::vector<std::vector<int>> map;
	loadLevel("./lib/Levels/lvl2.txt", map);
	int width = map[0].size();
	int height = map.size();

	createExRoom(&(manager->exroom),width, height, map);
}

void drawManager(Manager* manager){
	if(roomState == 1){
		drawExRoom(&(manager->exroom));
	}else{
	}
}

