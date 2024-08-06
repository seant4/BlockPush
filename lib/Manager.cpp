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
	createExRoom(&(manager->exroom));
}

void drawManager(Manager* manager){
	if(roomState == 1){
		drawExRoom(&(manager->exroom));
	}else{
	}
}

