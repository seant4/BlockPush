# Anada Engine
Anada Engine is a game engine written in C++ on top of the SDL2 library. The goal is to create a simple and easy to use game engine for rapid development of 2D games.

## Currently migrating to functional only

## Features:
- 2D Graphics
- I/O
- Collision Detection
- Physics
- Animation
- Text

## Workflow:
The workflow is designed to give you the starting point to add your own interactivity.

- Rooms:
	 Rooms serve as the entry point to what is on screen, each room manages what gets created and handles I/O

- Objects:
	 Objects are interactable elements within each room. Objects typically have graphics assigned to them, and can be set to be physical (collision detection). Objects can be controlled by the player or by AI.

From here, the idea is to use the built in rooms and objects class to add your own functionality

## TODO:
- ~~Physics~~
- ~~Sprite integration~~
- ~~Animation~~
- ~~Sound~~
- ~~UI~~

