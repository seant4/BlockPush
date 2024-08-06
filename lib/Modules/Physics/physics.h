#pragma once
#include <vector>

bool rectCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
std::vector<int> entityPhysics(int x, int y, std::vector<int> vel, std::vector<int> force);
