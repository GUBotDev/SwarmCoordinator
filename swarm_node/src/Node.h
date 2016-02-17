#pragma once

#include <cmath>
#include <string>
#include <iostream>
#include "Hardware.h"
#include "Write.h"
#include "ros/ros.h"
#include "mmapGpio.h"
#include "stdio.h"

class Node {
public:
	void moveToPosition(float x, float y);
	void locateBeacons(int beacon);
	void turnTo(float targetDirection);
	void locateOne();
	void locateTwo();
	void locateThree();
	void busy(bool);
private:
	const bool hasBeacon = true;//report relatively static xy position to master
	int beaconNum;//the number assigned by the master if the node has a beacon
	std::pair<bool, float> wasObjectFound;
	const float length = 0.25;//meters
	const float width = 0.25;//meters
	const float speed = 80;//mm per second
	const float formDis = 1;//meters
	const float checkY = 5;//meters
	const float checkXLeft = 2.5;
	const float checkXRight = 2.5;
	static Hardware hardware;
	static Write writer;
	float targetDirection;
	float currentDirection;
	float direction;
	float distance;
	float newY;
	float newX;
	float angle;
	float xPos;
	float yPos;
};
