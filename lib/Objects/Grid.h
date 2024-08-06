#ifndef GRID_H
#define GRID_H

#include <vector>

struct Grid {
    std::vector<std::vector<int>> matrix;
    int rows, cols;

    // Function to print the grid
    void print() const;

    // Function to check if a position is within the grid boundaries
    bool isValid(int x, int y) const;

    // Function to check if a position is free for moving (not a wall)
    bool canMove(int x, int y) const;

    // Function to move the player and the connected blocks
    void movePlayer(int startX, int startY, int dx, int dy);
};



void createGrid(Grid* grid, int r, int c, std::vector<std::vector<int>> temp);

#endif // GRID_H
