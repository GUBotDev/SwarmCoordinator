#pragma once

#include <string>
#include "FollowerNode.h"

//the mutator method is for the weak (change on transition to ROS)
class ControllerNode {
public:
	float direction;
	float xCenter;//relative point of origin x
	float yCenter;//relative point of origin y
	float length = 0.25;//meters
	float width = 0.25;//meters
	float beaconPosition[3][2] = { {-10, -10}, {10, 0}, {10, -10} };
	std::string beaconName;// or mac address
	void turn(float angle);
	void moveToPosition(float x, float y);
	FollowerNode* bots;//bots under control
	int numOfBots;//number of bots under control
private:

};