#include "FollowerNode.h"

void FollowerNode::turn(float angle) {//once this is turned, all followers will change positions
	//machine command - turn til compass equals

}

void FollowerNode::moveToPosition(float x, float y) {// moves single robot
	float newX = x - xPos;
	float newY = y - yPos;

	float angle = atan2(newY, newX);
	turn(angle);

	float distance = sqrt((newX * newX) + (newY * newY));
	moveForward(distance);
}

void FollowerNode::moveForward(float distance) {
	//machine command - move til distance equals (check with multilateration)

}