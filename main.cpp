#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <vector>
#ifdef DEBUG
#include <sstream>
#endif
#include "./lib/Manager.h"
#include "renderer.h"
#include "./lib/Modules/Visuals/dispText.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

SDL_Renderer* initRender(SDL_Window* window){
	//Window initialization
	SDL_Renderer* renderer = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
	}

	if(TTF_Init() < 0){
		fprintf(stderr, "Could not initialize SDL_TTF: %s\n", TTF_GetError());
	}
	window = SDL_CreateWindow(
			"Hello, World!",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
			);

	if (window == NULL){
		fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
	}
	//Create renderer
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	return renderer;
}

int main(int argc, char* args[]){
	unsigned int a = SDL_GetTicks();
	unsigned int b = SDL_GetTicks();
	double delta = 0;
	double framerate = 60.0; //Set framerate here
    renderer = initRender(window);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	#ifdef DEBUG
	TTF_Font* tnr = TTF_OpenFont("./Assets/fonts/tnr.ttf", 24);
	std::string inputText;
	SDL_StartTextInput();
	#endif
	SDL_RenderSetLogicalSize(renderer, 1280, 720);
	SDL_RenderSetVSync(renderer, 1);
    bool quit = false;
    SDL_Event e;
	//Typically set up room manager here
	Manager manager;
	createManager(&manager);
    while(!quit){
		#ifdef DEBUG
		bool renderText = false;
		#endif
		a = SDL_GetTicks();
		delta = a - b;
		if(delta > 1000/framerate){
			b=a;
			while(SDL_PollEvent(&e) != 0){
            	if(e.type==SDL_QUIT){
					updateManager(&manager, 10);
                	quit = true;
            	}
				//Handle user input here via SDL2 input handler, send this to manager
				if(e.type==SDL_KEYDOWN){
					switch(e.key.keysym.sym){ //IDK if this is optimal or if it even makes sense
						case SDLK_UP:
							updateManager(&manager, 1);
							break;
						case SDLK_DOWN:
							updateManager(&manager, 2);
							break;
						case SDLK_LEFT:
							updateManager(&manager, 3);
							break;
						case SDLK_RIGHT:
							updateManager(&manager, 4);
							break;
						case SDLK_r:
							updateManager(&manager, 5);
							break;

						#ifdef DEBUG
						case SDLK_BACKSPACE:
							if(inputText.size() > 0){ inputText.pop_back(); renderText = true; };
							break;
						case SDLK_RETURN:
							debugManager(&manager, inputText);
							inputText = "";
							break;
						#endif
					}
				}
				#ifdef DEBUG
				else if(e.type == SDL_TEXTINPUT){
					inputText += e.text.text;
					renderText = true;
				}
				#endif
        	}

			//Draw room manager here
			updateManager(&manager, 0);
			drawManager(&manager);
			//Debug mode
			#ifdef DEBUG
			char str[128];
			strcpy(str, "");
			double fps = (1000/delta);
			int round = static_cast<int>(fps+0.5);
			int b = manager.currentBoard;
			char bstr[128];
			strcat(str, "FPS: ");
			sprintf(bstr, "%d", round);
			strcat(str, bstr);
			sprintf(bstr, "%d", b);
			strcat(str, ", LEVEL: ");
			strcat(str, bstr);
			SDL_Rect back = {0,0,300,50};
			SDL_SetRenderDrawColor(renderer, 169,169,169,150);
			SDL_RenderFillRect(renderer, &back);
			dispText(0,0,200,50,str, tnr);
			if(inputText.size() > 0){
				char *instr = &inputText[0];
				dispText(300,0,300,100,instr, tnr);
			}
			#endif
        	SDL_RenderPresent(renderer);
		}
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
