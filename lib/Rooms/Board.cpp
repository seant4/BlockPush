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
#include "../Objects/Player.h"

using namespace std;

/* Position used in BFS search for edges and nodes */
typedef pair<int, int> Position;

/* Instantiates objects used in a given room
 *
 * @param
 * Board* room: Room object
 * int width: width of the game board
 * int height: height of the game board
 * std::vector<std::vector<int>> temp: Game board matrix (loaded from the room manager
 */
void createBoard(Board* room, int width, int height, std::vector<std::vector<int>> temp){
	const char *dir = "./assets/sprites/background.bmp";
    room->background = createTexture(dir);
	const char *dir2 = "./assets/sprites/block_sheet.bmp";
	room->block_sheet = createTexture(dir2);
	room->height = height;
	room->width = width;
	room->board = temp;
	room->scrollingOffset = 0;
	room->laser.dist = 0;
	//Find win condition tiles
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(room->board[i][j] == 4){
				room->wincon.emplace_back(i,j);
			}
		}
	}

	for(int i = 0; i < room->height; i++){
		for(int j = 0; j < room->width; j++){
			if(room->board[i][j] == 2){ //Player
			}else if(room->board[i][j] == 3){ //Wall
			}else if(room->board[i][j] == 1){ //Moveable block
			}else if(room->board[i][j] == 5){ //Border
			}else if(room->board[i][j] == 6){ //Vertical Laser
				room->laser.x = j;
				room->laser.y = i;
				room->laser.orientation = 0;
				room->laser.dist = 0;
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
	//Initialize local parameters
	int blockSize = 50;
	int yOffset = 30;
	int xOffset = 50;

	//Render background
	SDL_Rect dstrect = {room->scrollingOffset, 0, 1280, 720};
	SDL_RenderCopy(renderer, room->background, NULL, &dstrect);
	dstrect.x += 1280;
	dstrect.x += 25;
    SDL_RenderCopy(renderer, room->background, NULL, &dstrect);

	//Render back of gameboard
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect boardBack = {yOffset,xOffset,room->width * 50, room->height * 50};
	SDL_RenderFillRect(renderer, &boardBack);
	//Print win cons (These are stored seperately)	
	for(int i = 0; i < room->wincon.size(); i++){
		const auto& coord = room->wincon[i];
		drawWinBlock((coord.second * blockSize) + yOffset, (coord.first * blockSize) + xOffset , blockSize, blockSize, room->block_sheet);
	}	
	for(int i = 0; i < room->height; i++){
		for(int j = 0; j < room->width; j++){
			if(room->board[i][j] == 2){ //Player
				drawPlayer((j * blockSize)+ yOffset, (i * blockSize) + xOffset, blockSize, blockSize, room->block_sheet);
			}else if(room->board[i][j] == 3){ //Wall
				drawWall((j * blockSize) + yOffset, (i * blockSize) + xOffset, blockSize, blockSize, room->block_sheet);
			}else if(room->board[i][j] == 1){ //Moveable block
				drawBlock((j * blockSize) + yOffset, (i * blockSize) + xOffset, blockSize, blockSize, room->block_sheet);
			}else if(room->board[i][j] == 5){ //Border
				drawBorder((j * blockSize) + yOffset, (i * blockSize) + xOffset, blockSize, blockSize, room->block_sheet);
			}else if(room->board[i][j] == 6){ //Vertical Laser
				drawLaser(&(room->laser), (j * blockSize)+yOffset, (i * blockSize) + xOffset);
			}
		}
	}
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
 * 	through eachother to the player
 */
vector<Position> findGroup(Board* room, const Position& start_pos, int type){
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
			if(room->board[next_pos.first][next_pos.second] == type &&
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
 * Board* room: Room object
 * const vector<Position>& block_group: Vector of positions of all blocks in a group
 * 	(typically found by findGroup)
 * const Position& direction: Direction vector in which to move
 *
 * @return:
 * boolean: successful or unsuccessful move
 */
bool moveGroup(Board* room, const vector<Position>& block_group, const Position& direction){
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
 * Board* room: Room object
 * Position& player_pos: Players current position
 * const Position& direction: Direction to move
 *
 * @return
 * boolean: Successful or unsuccessful move
 */
bool movePlayer(Board* room, Position& player_pos, const Position& direction){
	Position new_player_pos = {player_pos.first	+ direction.first, player_pos.second + direction.second};
	if(room->board[new_player_pos.first][new_player_pos.second] == 3 || room->board[new_player_pos.first][new_player_pos.second] == 5){
		return false;
	}
	//TODO: Update to take block type (more block types in future)
	if(room->board[new_player_pos.first][new_player_pos.second] == 1){
		vector<Position> block_group = findGroup(room, new_player_pos, 1);
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


/* Checks where new connections are made (For visual signal)
 *
 */

void newConnections(std::vector<std::vector<int>> prev, std::vector<std::vector<int>> next){
	int adj = 0;
	for(int i = 0; i < prev.size(); i++){
		for(int j = 0; j < prev[i].size(); j++){
			if(prev[i][j] == 0 && next[i][j] == 1){
				if(prev[i+1][j] == 1){
					adj++;
				}if(prev[i-1][j] == 1){
					adj++;
				}if(prev[i][j+1] == 1){
					adj++;
				}if(prev[i][j-1] == 1){
					adj++;
				}
				if(adj >= 2){
					printf("New connection made");
				}else{
					adj = 0;
				}
			}
		}
	}
}


/* Update and checks room logic
 *
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
	std::vector<std::vector<int>> previous = room->board;
	--(room->scrollingOffset);
	if(room->scrollingOffset < -1280){
		room->scrollingOffset = 0;
	}
	//Update moving background
	Position player_pos;
	for(int i = 0; i < room->height; i++){
		for(int j = 0; j < room->width; j++){
			if(room->board[i][j] == 2){
				player_pos = {i, j};
			}
		}
	}

	bool flag = true;
	//Wincon checking theoretically doesnt need to happen unless the player moves (refactor this)
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

	if(updateLaser(&(room->laser), room->board)){
		return 3;
	}
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
