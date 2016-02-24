#pragma once

#include <cmath>
#include <string>
#include <iostream>
#include <math.h>
#include <tuple>
#include "Calculation.h"
#include "Hardware.h"
#include "mmapGpio.h"
#include "stdio.h"

class Node {
public:
	void moveToPosition(float x, float y, float xPos, float yPos);
	void turnTo(float targetDirection);
	std::pair<float, float> returnXY();
	void checkTolerances(float angle);
	void checkTolerances(float x, float y, float xPos, float yPos);
private:
	const bool hasBeacon = false;//report relatively static xy position to master
	int beaconNum;//the number assigned by the master if the node has a beacon
	//const std::string beaconAddress = "EB:E7:B3:42:48:89";
	std::pair<bool, float> wasObjectFound;
	const float length = 0.25;//meters
	const float width = 0.25;//meters
	const float speed = 80;//mm per second
	const float formDis = 1;//meters
	const float checkY = 5;//meters
	const float checkXLeft = 2.5;
	const float checkXRight = 2.5;
	const float positionTolerance = 0.25;//+/- meters
	const float checkIncrement = 0.25;//+/- meters
	const float scanDistance = 2.5;
	const float angleTolerance = 10;//+/-degrees
	bool beaconsSet = false;
	static Calculation calculate;
	static Hardware hardware;
	float xBeacons[4] = { -1, 1, -1, 1 };
	float yBeacons[4] = { 1, 1, -1, -1 };
	std::string beaconID[4] = { "CA:5D:E6:8B:34:58", "D0:16:DF:6C:6E:E1", "C8:04:02:87:D1:CA", "EB:E7:B3:42:48:89"};
	int numBeacons = 4;
	float targetDirection;
	float currentDirection;
	float direction;
	float distance;
	float angle;
	float newY;
	float newX;
	float lastX;
	float lastY;
	float baseDirection;
};
