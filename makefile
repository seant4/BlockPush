debug ?= false
ifeq ($(debug), true)
	DEBUG_FLAGS = -pg -g -DDEBUG
else
	DEBUG_FLAGS =
endif



compile:./main.cpp
	g++ $(DEBUG_FLAGS) -I ./lib/ -o build/app.o main.cpp renderer.cpp -lSDL2 -lSDL2_ttf ./lib/*.cpp ./lib/Rooms/*.cpp ./lib/Entities/*.cpp ./lib/Modules/*/*.cpp

run:
	build/app.o
