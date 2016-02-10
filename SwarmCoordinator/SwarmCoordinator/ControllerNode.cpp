#include "ControllerNode.h"

void ControllerNode::turn(float angle) {//once this is turned, all followers will change positions
	//machine command - turn til compass equals

}

void ControllerNode::moveToPosition(float x, float y) {// moves entire system - relative coordinates are changed
	float newX = x - xCenter;
	float newY = y - yCenter;
	
	float angle = atan2(newY, newX);
	turn(angle);

	float distance = sqrt((newX * newX) + (newY * newY));
	moveForward(distance);
}

void ControllerNode::moveForward(float distance) {
	//machine command - move til distance equals (check with multilateration)

}