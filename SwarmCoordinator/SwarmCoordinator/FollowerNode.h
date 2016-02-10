#pragma once

#include <cmath>
#include <string>

class FollowerNode {
public:
	float direction;
	float xPos;
	float yPos;
	float length = 0.25;//meters
	float width = 0.25;//meters
	void turn(float angle);
	void moveToPosition(float x, float y);
	void moveForward(float distance);
private:

};