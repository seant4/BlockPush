/* Instantiates and manages logic related to the game board and
 * board levels
 */

#include "ExRoom.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include "../../renderer.h"
#include "../Modules/Visuals/createTexture.h"
#include "../Objects/Player.h"
using namespace std;

/* Position used in BFS search for edges and nodes */
typedef pair<int, int> Position;

/* Instantiates objects used in a given room
 *
 * @param
 * ExRoom* room: Room object
 * int width: width of the game board
 * int height: height of the game board
 * std::vector<std::vector<int>> temp: Game board matrix (loaded from the room manager
 */
void createExRoom(ExRoom* room, int width, int height, std::vector<std::vector<int>> temp){
	const char *dir = "./assets/sprites/background.bmp";
    room->background = createTexture(dir);
	const char *dir2 = "./assets/sprites/block_sheet.bmp";
	room->block_sheet = createTexture(dir2);
	room->height = height;
	room->width = width;
	room->board = temp;
	//Find win condition tiles
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(room->board[i][j] == 4){
				room->wincon.emplace_back(i,j);
			}
		}
	}
}

/* Draws objects within the room
 *
 * @param
 * ExRoom* room: Room object
 */
void drawExRoom(ExRoom* room){
	int blockSize = 50;
    SDL_RenderCopy(renderer, room->background, NULL, NULL);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect boardBack = {0,0,room->width * 50, room->height * 50};
	SDL_RenderFillRect(renderer, &boardBack);
	//Print win cons (These are stored seperately)	
	for(int i = 0; i < room->wincon.size(); i++){
		const auto& coord = room->wincon[i];
		drawWinBlock(coord.second * blockSize, coord.first * blockSize , blockSize, blockSize, room->block_sheet);
	}	
	for(int i = 0; i < room->height; i++){
		for(int j = 0; j < room->width; j++){
			if(room->board[i][j] == 2){ //Player
				drawPlayer(j * blockSize, i * blockSize, blockSize, blockSize, room->block_sheet);
			}else if(room->board[i][j] == 3){ //Wall
				drawWall(j * blockSize, i * blockSize, blockSize, blockSize, room->block_sheet);
			}else if(room->board[i][j] == 1){ //Moveable block
				drawBlock(j * blockSize, i * blockSize, blockSize, blockSize, room->block_sheet);
			}else if(room->board[i][j] == 5){ //Border
				drawBorder(j * blockSize, i * blockSize, blockSize, blockSize, room->block_sheet);
			}
		}
	}
}

/* BFS algorithm to find connections between the player object and 
 * block objects
 *
 * @param
 * ExRoom* room: Room object
 * const Position& start_pos: Starting position of bfs
 *
 * @return
 * 2d vector containing the positions of all blocks connected 
 * 	through eachother to the player
 */
vector<Position> findGroup(ExRoom* room, const Position& start_pos){
	vector<Position> group;
	vector<vector<bool>> visited(room->height, vector<bool>(room->width, false));
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
			if(room->board[next_pos.first][next_pos.second] == 1 &&
					!visited[next_pos.first][next_pos.second]){
				to_visit.push(next_pos);
			}
		}
	}
	return group;
}

/* Moves a given block group in some direction
 *
 * @param:
 * ExRoom* room: Room object
 * const vector<Position>& block_group: Vector of positions of all blocks in a group
 * 	(typically found by findGroup)
 * const Position& direction: Direction vector in which to move
 *
 * @return:
 * boolean: successful or unsuccessful move
 */
bool moveGroup(ExRoom* room, const vector<Position>& block_group, const Position& direction){
	vector<Position> new_positions;
	for(const auto& pos: block_group){
		Position new_pos = {pos.first + direction.first, pos.second + direction.second};
		if(room->board[new_pos.first][new_pos.second] == 3 || room->board[new_pos.first][new_pos.second] == 5 ||
				(room->board[new_pos.first][new_pos.second] == 1 &&
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
		room->board[new_pos.first][new_pos.second] = 1;
	}

	return true;
}

/* Moves player around the room
 *
 * @param
 * ExRoom* room: Room object
 * Position& player_pos: Players current position
 * const Position& direction: Direction to move
 *
 * @return
 * boolean: Successful or unsuccessful move
 */
bool movePlayer(ExRoom* room, Position& player_pos, const Position& direction){
	Position new_player_pos = {player_pos.first	+ direction.first, player_pos.second + direction.second};
	if(room->board[new_player_pos.first][new_player_pos.second] == 3 || room->board[new_player_pos.first][new_player_pos.second] == 5){
		return false;
	}
	if(room->board[new_player_pos.first][new_player_pos.second] == 1){
		vector<Position> block_group = findGroup(room, new_player_pos);
		if(!(moveGroup(room, block_group, direction))){
			return false;
		}
	}

	//Move player
	if(room->board[player_pos.first][player_pos.second] == 1){
		room->board[player_pos.first][player_pos.second] = 1;
		room->board[new_player_pos.first][new_player_pos.second] = 2;
		player_pos = new_player_pos;
	}else{
		room->board[player_pos.first][player_pos.second] = 0;
		room->board[new_player_pos.first][new_player_pos.second] = 2;
		player_pos = new_player_pos;
	}

	return true;
}


/* Update and checks room logic
 *
 * @param
 * ExRoom* room: Room object
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
int updateExRoom(ExRoom* room, int key){
	Position player_pos;
	for(int i = 0; i < room->height; i++){
		for(int j = 0; j < room->width; j++){
			if(room->board[i][j] == 2){
				player_pos = {i, j};
			}
		}
	}
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
	}
	//Check if win condition is met
	bool flag = true;
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
