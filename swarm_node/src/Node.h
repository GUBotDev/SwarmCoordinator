#pragma once

#include <cmath>
#include <string>
#include "Movement.h"
#include "mmapGpio.h"
#include "stdio.h"

class Node {
public:
	void moveToPosition(float x, float y);
	void locateBeacons();
	void fullScan();
	void locateOne();
	void locateTwo();
	void locateThree();
private:
	const bool hasBeacon = true;//report relatively static xy position to master
	const int turnIncrement = 5;//degrees
	int beaconNum;//the number assigned by the master if the node has a beacon
	std::pair<bool, float> wasObjectFound;
	float direction;
	float xPos;
	float yPos;
	float newY;
	float newX;
	float angle;
	float distance;
	const float length = 0.25;//meters
	const float width = 0.25;//meters
	const float speed = 80;//mm per second
	bool isBusy = false;
	Movement moveNode;
};
