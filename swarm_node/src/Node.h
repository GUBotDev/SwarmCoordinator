#pragma once

#include <cmath>
#include <string>
#include <iostream>
#include <math.h>
#include <tuple>
#include "Calculation.h"
#include "Hardware.h"
#include "Write.h"
#include "ros/ros.h"
#include "mmapGpio.h"
#include "stdio.h"

class Node {
public:
	void moveToPosition(float x, float y, float xPos, float yPos);
	void turnTo(float targetDirection);
	void locateOne();
	void locateTwo(float direction);
	void locateThree(std::string beaconIDOne, std::string beaconIDTwo, float direction);
	void busy(bool);
	std::pair<float, float> returnXY();
	void checkTolerances(float angle);
	void checkTolerances(float x, float y, float xPos, float yPos);
	void requestBeacons();
	void setBeacons(float* x, float* y, std::string* ID, int numBeacons);
	void objectFound(float x, float y, float distance);
	void initialize();
	void alreadyInitialized();
	void unknownCommand(std::string data);
	void sendLastPositionDirection();
	void sendPositionDirection(float x, float y, bool obstacle);
	void setBeacon(int input);
	int getBeacon();
private:
	const bool hasBeacon = true;//report relatively static xy position to master
	int beaconNum;//the number assigned by the master if the node has a beacon
	const std::string beaconAddress = "EB:E7:B3:42:48:89";
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
	static Write writer;
	float* xBeacons;
	float* yBeacons;
	std::string* beaconID;
	int numBeacons;
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
