
debug ?= false
ifeq ($(debug), true)
	DEBUG_FLAGS = -pg -g
else
	DEBUG_FLAGS =
endif

compile:./main.cpp
	g++ $(DEBUG_FLAGS) -I ./lib/ -o app.o main.cpp  renderer.cpp -lSDL2 -lSDL2_ttf ./lib/*.cpp ./lib/Rooms/*.cpp ./lib/Objects/*.cpp ./lib/Modules/Physics/*.cpp ./lib/Modules/Visuals/*.cpp

d:./main.cpp
	g++ -pg -g -I ./lib/ -o app.o main.cpp  renderer.cpp -lSDL2 -lSDL2_ttf ./lib/*.cpp ./lib/Rooms/*.cpp ./lib/Objects/*.cpp ./lib/Modules/Physics/*.cpp ./lib/Modules/Visuals/*.cpp

time:./main.cpp
	g++ -pg -g -I ./lib/ -o app.o main.cpp  renderer.cpp -lSDL2 -lSDL2_ttf ./lib/*.cpp ./lib/Rooms/*.cpp ./lib/Objects/*.cpp ./lib/Modules/Physics/*.cpp ./lib/Modules/Visuals/*.cpp

run:
	./app.o
