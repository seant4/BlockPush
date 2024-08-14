/* Instantiates and manages logic related to the game board and
 * board levels
 */

#include "Board.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include "../../renderer.h"
#include "../Modules/Visuals/createTexture.h"

using namespace std;

/* Position used in BFS search for edges and nodes */
typedef pair<int, int> Position;

#define blockSize 100
#define yOffset 315
#define xOffset 20

/* Instantiates objects used in a given room
 *
 * @param
 * Board* room: Room object
 * int width: width of the game board
 * int height: height of the game board
 * std::vector<std::vector<int>> temp: Game board matrix (loaded from the room manager
 */
void createBoard(Board* room, int width, int height, std::vector<std::vector<int>> temp, int f){
	/* Define initial variables and load textures */
	const char *dir1 = "./assets/sprites/background.bmp";
	room->frame = 0;
	room->background = createTexture(dir1);
	room->nlasers = 0;
	const char *dir2 = "./assets/sprites/block_sheet.bmp";
	room->block_sheet = createTexture(dir2);
	room->height = height;
	room->width = width;
	room->board.clear();
	room->board = temp;
	room->wincon.clear();
	room->scrollingOffset=0;

	/* Load entities from board matrix
	 *
	 * This allows the game to manage the state of the entities 
	 * on the board, such as the lasers and blocks
	 *
	 */
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(room->board[i][j] == 4){
				room->wincon.emplace_back(i,j);
			}
		}
	}
	
	// Delete old entity data if we are loading a new board
	if(f == 2){
		free(room->lasers);
		for(int i = 0; i < room->block1; i++){
			free(room->blocks1[i]);
		}
		for(int i = 0; i < room->block2; i++){
			free(room->blocks2[i]);
		}
		free(room->blocks1);
		free(room->blocks2);
	}

	// Allocate arrays for each set of entities
	room->nlasers = 0;
	room->block1 = 0;
	room->block2 = 0;
	for(int i = 0; i < room->height; i++){
		for(int j = 0; j < room->width; j++){
			if(room->board[i][j] == 2){ //Player
			}else if(room->board[i][j] == 3){ //Wall
			}else if(room->board[i][j] == 1){ //Moveable block
				room->block1++;
			}else if(room->board[i][j] == 5){ //Border
			}else if(room->board[i][j] == 6){ //Vertical Laser
				room->nlasers++;
			}else if(room->board[i][j] == 7){ //Horizontal Laser
				room->nlasers++;
			}else if(room->board[i][j] == 8){ //Moveable block 2
				room->block2++;
			}
		}
	}
	room->lasers = static_cast<Laser*>(malloc(room->nlasers * sizeof(Laser)));
	room->blocks1 = (int**)(malloc(room->block1 * sizeof(int *)));
	room->blocks2 = (int**)(malloc(room->block2 * sizeof(int *)));
	int s = 0;
	int b1 = 0;
	int b2 = 0;

	//Load all of the entities in to their respective arrays
	for(int i = 0; i < room->height; i++){
		for(int j = 0; j < room->width; j++){
			if(room->board[i][j] == 1){ //Moveable block
				room->blocks1[b1] = (int*)(malloc(2 * sizeof(int)));
				room->blocks1[b1][0] = (j * blockSize) + yOffset;
				room->blocks1[b1][1] = (i * blockSize) + xOffset;
				b1++;
			}
			if(room->board[i][j] == 6){ //Vertical Laser
				room->lasers[s].x = j;
				room->lasers[s].y = i;
				room->lasers[s].orientation = 0;
				room->lasers[s].dist = 0;
				s++;
			}else if(room->board[i][j] == 7){ //Horizontal Laser
				room->lasers[s].x = j;
				room->lasers[s].y = i;
				room->lasers[s].orientation = 1;
				room->lasers[s].dist = 0;
				s++;
			}else if(room->board[i][j] == 8){
				room->blocks2[b2] = (int*)(malloc(2 * sizeof(int)));
				room->blocks2[b2][0] = (j * blockSize) + yOffset;
				room->blocks2[b2][1] = (i * blockSize) + xOffset;
				b2++;
			}
		}
	}
}

/* Draws objects within the room
 *
 * @param
 * Board* room: Room object
 */
void drawBoard(Board* room){

	//Render background
	SDL_Rect dest = {room->scrollingOffset,0,1920,1080};
	SDL_RenderCopy(renderer, room->background, NULL, &dest);
	dest = {room->scrollingOffset + 1920, 0, 1920, 1080};
	SDL_RenderCopy(renderer, room->background, NULL, &dest);
	//Render back of gameboard
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect boardBack = {yOffset,xOffset,room->width * 100, room->height * 100};
	SDL_RenderFillRect(renderer, &boardBack);

	//Print win cons (These are stored seperately)	
	for(int i = 0; i < room->wincon.size(); i++){
		const auto& coord = room->wincon[i];
		drawWinBlock((coord.second * blockSize) + yOffset, (coord.first * blockSize) + xOffset , blockSize, blockSize, room->block_sheet);
	}

	//Get draw pos of every block on the board (used for finding connections between blocks
	int b1 = 0;
	int b2 = 0;
	if(room->blocks1 != NULL){
		for(int i = 0; i < room->height; i++){
			for(int j = 0; j < room->width; j++){
				if(room->board[i][j] == 1){
					room->blocks1[b1][0] = (j * blockSize) + yOffset;
					room->blocks1[b1][1] = (i * blockSize) + xOffset;
					b1++;
				}else if(room->board[i][j] == 8){
					room->blocks2[b2][0] = (j * blockSize) + yOffset;
					room->blocks2[b2][1] = (i * blockSize) + xOffset;
					b2++;
				}
			}
		}
	}

	//Draw each item on the board
	int l = 0;
	for(int i = 0; i < room->height; i++){
		for(int j = 0; j < room->width; j++){
			if(room->board[i][j] == 2){ //Player
				drawPlayer((j * blockSize)+ yOffset, (i * blockSize) + xOffset, blockSize, blockSize, room->block_sheet);
			}else if(room->board[i][j] == 3){ //Wall
				drawWall((j * blockSize) + yOffset, (i * blockSize) + xOffset, blockSize, blockSize, room->block_sheet);
			}else if(room->board[i][j] == 1){ //Moveable block
				if(room->blocks1 != NULL){
					drawBlock((j * blockSize) + yOffset, (i * blockSize) + xOffset, blockSize, blockSize, room->block_sheet, room->blocks1, room->block1, 1);
				}
			}else if(room->board[i][j] == 5){ //Border
				drawBorder((j * blockSize) + yOffset, (i * blockSize) + xOffset, blockSize, blockSize, room->block_sheet);
			}else if(room->board[i][j] == 6){ //Vertical Laser		
				if(room->lasers != NULL){
					room->lasers[l].draw((j*blockSize) + yOffset, (i * blockSize) + xOffset, room->block_sheet);
					l++;
				}
			}else if(room->board[i][j] == 7){ //Horizontal Laser
				if(room->lasers != NULL){
					room->lasers[l].draw((j*blockSize) + yOffset, (i * blockSize) + xOffset, room->block_sheet);
					l++;
				}
			}else if(room->board[i][j] == 8){ //Moveable block
				if(room->blocks2 != NULL){
					drawBlock((j * blockSize) + yOffset, (i * blockSize) + xOffset, blockSize, blockSize, room->block_sheet, room->blocks2, room->block2, 8);
				}
			}else if(room->board[i][j] == 9){ //NPC
				drawScientist((j * blockSize) + yOffset, (i * blockSize) + xOffset,blockSize,blockSize, 6, room->frame, room->block_sheet);
			}
		}
	}
	room->frame++;
}

/* BFS algorithm to find connections between the player object and 
 * block objects
 *
 * @param
 * Board* room: Room object
 * const Position& start_pos: Starting position of bfs
 *
 * @return
 * 2d vector containing the positions of all blocks connected 
 * 	through eachother to the player (or some starting position)
 */
vector<Position> boardBFS(std::vector<std::vector<int>> board, int type, const Position& start_pos){
	vector<Position> group;
	vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));
	queue<Position> to_visit;
	to_visit.push(start_pos);

	while(!to_visit.empty()){
		Position pos = to_visit.front();
		to_visit.pop();

		if(visited[pos.first][pos.second]){
			continue;
		}

		visited[pos.first][pos.second] = true;
		group.push_back(pos);

		vector<Position> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
		for(const auto& dir: directions){
			Position next_pos = {pos.first + dir.first, pos.second + dir.second};
			if(board[next_pos.first][next_pos.second] == type &&
					!visited[next_pos.first][next_pos.second]){
				to_visit.push(next_pos);
			}
		}
	}
	return group;
}

vector<Position> findGroup(Board* room, const Position& start_pos, int type){
	return(boardBFS(room->board,type,start_pos)); 
}

/* Moves a given block group in some direction
 *
 * @param:
 * Board* room: Room object
 * const vector<Position>& block_group: Vector of positions of all blocks in a group
 * 	(typically found by findGroup)
 * const Position& direction: Direction vector in which to move
 *
 * @return:
 * boolean: successful or unsuccessful move
 */
bool moveGroup(Board* room, const vector<Position>& block_group, const Position& direction, int type){
	vector<Position> new_positions;
	for(const auto& pos: block_group){
		Position new_pos = {pos.first + direction.first, pos.second + direction.second};
		//TODO: Refactor this
		if(!(room->board[new_pos.first][new_pos.second] == type || room->board[new_pos.first][new_pos.second] == 0 || room->board[new_pos.first][new_pos.second] == 4 || room->board[new_pos.first][new_pos.second] == 2)
				|| (room->board[new_pos.first][new_pos.second] == type &&
				 find(block_group.begin(), block_group.end(), new_pos) == block_group.end())) {
			return false;
		}
		new_positions.push_back(new_pos);
	}
	for(size_t i = 0; i < block_group.size(); i++){
		const auto& old_pos = block_group[i];
		const auto& new_pos = new_positions[i];
	}
	for(size_t i = 0; i < block_group.size(); i++){
		const auto& old_pos = block_group[i];
		const auto& new_pos = new_positions[i];
		room->board[old_pos.first][old_pos.second] = 0;
	}
	for(size_t i = 0; i < block_group.size(); i++){
		const auto& old_pos = block_group[i];
		const auto& new_pos = new_positions[i];
		room->board[new_pos.first][new_pos.second] = type ;
	}

	return true;
}

/* Moves player around the room
 *
 * @param
 * Board* room: Room object
 * Position& player_pos: Players current position
 * const Position& direction: Direction to move
 *
 * @return
 * boolean: Successful or unsuccessful move
 */
bool movePlayer(Board* room, Position& player_pos, const Position& direction){
	//Get the new position of the player
	Position new_player_pos = {player_pos.first	+ direction.first, player_pos.second + direction.second};

	//If they hit a wall or a barrier
	if(room->board[new_player_pos.first][new_player_pos.second] == 3 || room->board[new_player_pos.first][new_player_pos.second] == 5 || 
			room->board[new_player_pos.first][new_player_pos.second] == 9){
		return false;
	}

	//If they hit a moveable bock
	if(room->board[new_player_pos.first][new_player_pos.second] == 1){
		vector<Position> block_group = findGroup(room, new_player_pos, 1);
		if(!(moveGroup(room, block_group, direction, 1))){
			return false;
		}
	}
	if(room->board[new_player_pos.first][new_player_pos.second] == 8){
		vector<Position> block_group = findGroup(room, new_player_pos, 8);
		if(!(moveGroup(room, block_group, direction, 8))){
			return false;
		}
	}

	//Update the players location, and update their previous location
	int prev = 0;
	if(!( room->board[player_pos.first][player_pos.second] == 2 ||  room->board[player_pos.first][player_pos.second] == 3 || room->board[player_pos.first][player_pos.second] == 4)){
		prev = room->board[player_pos.first][player_pos.second];
	}else{
		prev = 0;
	}
	room->board[player_pos.first][player_pos.second] = prev;
	room->board[new_player_pos.first][new_player_pos.second] = 2;

	return true;
}

/* Update and checks room logic
 * @param
 * Board* room: Room object
 * int key: Key press binding
 *
 * @return
 * int: State of the room
 */
/* Key:
 * 1 = up
 * 2 = down
 * 3 = left
 * 4 = right
 */
/* Returns:
 * 1 = No change
 * 2 = Beat level
 * 3 = Reset level
 */
int updateBoard(Board* room, int key){
	//Update moving background
	--(room->scrollingOffset);
	if(room->scrollingOffset < -1920){
		room->scrollingOffset = 0;
	}

	//Find the players position
	Position player_pos;
	for(int i = 0; i < room->height; i++){
		for(int j = 0; j < room->width; j++){
			if(room->board[i][j] == 2){
				player_pos = {i, j};
			}
		}
	}

	//Update room based on user input
	bool flag = true;
	switch(key){
		case 1:
			movePlayer(room, player_pos, {-1,0});
			break;
		case 2:
			movePlayer(room, player_pos, {1,0});
			break;
		case 3:
			movePlayer(room, player_pos, {0, -1});
			break;
		case 4:
			movePlayer(room, player_pos, {0, 1});
			break;
		case 5:
			return 3;
			break;
		case 10:
			free(room->lasers);
			for(int i = 0; i < room->block1; i++){
				free(room->blocks1[i]);
			}
			free(room->blocks1);
			for(int i = 0; i < room->block2; i++){
				free(room->blocks2[i]);
			}
			free(room->blocks2);
			room->lasers = NULL;
			room->blocks1 = NULL;
			room->blocks2 = NULL;
			break;
	}

	//Update the lasers
	if(room->lasers != NULL){
		for(int i = 0; i < room->nlasers; i++){
			if(room->lasers[i].update(room->board)){
				return 3;
			}
		}
	}
	
	//Detect the win condition
	for(int i = 0; i < room->wincon.size(); i++){
		const auto& coord = room->wincon[i];
		if(!(room->board[coord.first][coord.second] == 1)){
			flag = false;
		}
	}	
	if(flag){
		return 2;
	}
	return 1;
}
