#include <stdio.h>
#include <SDL2/SDL.h>
#include "Manager.h"
#include "../renderer.h"
#include "roomstate.h"

#include "./Rooms/ExRoom.h"

void updateManager(Manager* manager, int key){
	updateExRoom(&(manager->exroom), key);
}

void createManager(Manager* manager){

	int width = 12;
	int height = 6;

	std::vector<std::vector<int>> map = {
		{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
		{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
		{3, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3},
		{3, 0, 1, 2, 0, 3, 0, 0, 0, 1, 0, 3},
		{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
		{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}
	};
	createExRoom(&(manager->exroom),width, height, map);
}

void drawManager(Manager* manager){
	if(roomState == 1){
		drawExRoom(&(manager->exroom));
	}else{
	}
}

