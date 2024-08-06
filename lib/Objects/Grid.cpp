#include "Grid.h"
#include <iostream>
#include <queue>

using namespace std;

const int EMPTY = 0;
const int PLAYER = 2;
const int BLOCK = 1;
const int WALL = 3;
const int DIRECTIONS[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right


void createGrid(Grid* grid, int r, int c, std::vector<std::vector<int>> vect){
	grid->rows = r;
	grid->cols = c;
	grid->matrix = vect;
}

void Grid::print() const {
    for (const auto& row : matrix) {
        for (int cell : row) {
			std::cout << cell << " ";
        }
		std::cout << std::endl;
    }
}

bool Grid::isValid(int x, int y) const {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

bool Grid::canMove(int x, int y) const {
    return isValid(x, y) && matrix[x][y] != WALL;
}

void Grid::movePlayer(int startX, int startY, int dx, int dy) {
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<pair<int, int>> formation; // Stores all cells in the formation

    q.push({startX, startY});
    visited[startX][startY] = true;
    formation.push_back({startX, startY});

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (const auto& dir : DIRECTIONS) {
            int newX = x + dir[0];
            int newY = y + dir[1];

            if (isValid(newX, newY) && !visited[newX][newY]) {
                visited[newX][newY] = true;
                formation.push_back({newX, newY});

                if (matrix[newX][newY] == EMPTY || matrix[newX][newY] == PLAYER || matrix[newX][newY] == BLOCK) {
                    q.push({newX, newY});
                }
            }
        }
    }

    // Move the player
    int newPlayerX = startX + dx;
    int newPlayerY = startY + dy;

    if (canMove(newPlayerX, newPlayerY)) {
        matrix[startX][startY] = EMPTY;
        matrix[newPlayerX][newPlayerY] = PLAYER;
        startX = newPlayerX;
        startY = newPlayerY;
    }

    // Separate movement for blocks
    vector<pair<int, int>> movedBlocks;
    vector<pair<int, int>> blockedBlocks;

    for (const auto& [x, y] : formation) {
        int newX = x + dx;
        int newY = y + dy;

        if (matrix[x][y] == BLOCK) {
            if (canMove(newX, newY) && matrix[newX][newY] == EMPTY) {
                movedBlocks.push_back({x, y});
                matrix[x][y] = EMPTY;
                matrix[newX][newY] = BLOCK;
            } else if (!canMove(newX, newY)) {
                blockedBlocks.push_back({x, y});
            }
        }
    }

    // Handle movement of blocks behind the wall
    for (const auto& [x, y] : blockedBlocks) {
        int newX = x + dx;
        int newY = y + dy;

        if (canMove(newX, newY) && matrix[newX][newY] == EMPTY) {
            matrix[x][y] = EMPTY;
            matrix[newX][newY] = BLOCK;
        }
    }
}