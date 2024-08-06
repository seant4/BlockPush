compile:./main.cpp
	g++ -I ./lib/ -o app.o main.cpp  renderer.cpp -lSDL2 -lSDL2_ttf ./lib/*.cpp ./lib/Rooms/*.cpp ./lib/Objects/*.cpp ./lib/Modules/Physics/*.cpp ./lib/Modules/Visuals/*.cpp

debug:./main.cpp
	g++ -g -I ./lib/ -o app.o main.cpp  renderer.cpp -lSDL2 -lSDL2_ttf ./lib/*.cpp ./lib/Rooms/*.cpp ./lib/Objects/*.cpp ./lib/Modules/Physics/*.cpp ./lib/Modules/Visuals/*.cpp

run:
	./app.o
