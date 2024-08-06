#include <vector>

std::vector<int> entityPhysics(int x, int y, std::vector<int> vel, std::vector<int> force){
	//Apply gravity
	vel[0] += force[0];
	vel[1] += (force[1] + 1); //gravity
	return std::vector<int>{vel[0], vel[1]};
}

bool rectCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2){
	if(x1 >= x2+w2 || x2 >= x1+w1){
		return false;
	}

	if(y1 >= y2+h2 || y2 >= y1+h1){
		return false;
	}
	return true;
}
