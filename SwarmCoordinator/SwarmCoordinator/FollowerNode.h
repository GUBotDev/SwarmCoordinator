#pragma once

class FollowerNode {
public:
	float direction;
	float xPos;
	float yPos;
	float length = 0.25;//meters
	float width = 0.25;//meters
	void moveToPosition(float x, float y);
private:

};