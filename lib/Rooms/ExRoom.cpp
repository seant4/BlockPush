#include "ExRoom.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include "../../renderer.h"
#include "../Modules/Visuals/createTexture.h"
#include "../Objects/Player.h"
using namespace std;

typedef pair<int, int> Position;

void createExRoom(ExRoom* room, int width, int height, std::vector<std::vector<int>> temp){
	const char *dir = "./assets/sprites/background.bmp";
    room->background = createTexture(dir);
	room->height = height;
	room->width = width;
	room->board = temp;
}

void drawExRoom(ExRoom* room){
	int blockSize = 50;
    SDL_RenderCopy(renderer, room->background, NULL, NULL);
	for(int i = 0; i < room->height; i++){
		for(int j = 0; j < room->width; j++){
			if(room->board[i][j] == 2){
				drawPlayer(j * blockSize, i * blockSize, blockSize, blockSize);
			}else if(room->board[i][j] == 3){
				drawWall(j * blockSize, i * blockSize, blockSize, blockSize);
			}else if(room->board[i][j] == 1){
				drawBlock(j * blockSize, i * blockSize, blockSize, blockSize);
			}
		}
	}
}


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

bool moveGroup(ExRoom* room, const vector<Position>& block_group, const Position& direction){
	vector<Position> new_positions;
	for(const auto& pos: block_group){
		Position new_pos = {pos.first + direction.first, pos.second + direction.second};
		if(room->board[new_pos.first][new_pos.second] == 3 ||
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

bool movePlayer(ExRoom* room, Position& player_pos, const Position& direction){
	Position new_player_pos = {player_pos.first	+ direction.first, player_pos.second + direction.second};
	if(room->board[new_player_pos.first][new_player_pos.second] == 3){
		return false;
	}
	if(room->board[new_player_pos.first][new_player_pos.second] == 1){
		vector<Position> block_group = findGroup(room, new_player_pos);
		if(!(moveGroup(room, block_group, direction))){
			return false;
		}
	}

	//Move player
	room->board[player_pos.first][player_pos.second] = 0;
	room->board[new_player_pos.first][new_player_pos.second] = 2;
	player_pos = new_player_pos;
	return true;
}



/* Key:
 * 1 = up
 * 2 = down
 * 3 = left
 * 4 = right
 */
void updateExRoom(ExRoom* room, int key){
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
	}
}
