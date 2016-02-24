#pragma once

#include <cmath>
#include <array>
#include <vector>
#include <iostream>
#include <tuple>
#include <math.h>
#include "mmapGpio.h"
#include "stdio.h"
#include <unistd.h>//unix sleep
#include <chrono>//timer
#include <sstream>

typedef std::chrono::high_resolution_clock Clock;

class Hardware {
public:
	void turn(float targetDirection);
	std::pair<bool, float> moveForward(float meters);
	std::pair<bool, float> moveBackward(float meters);
	std::tuple<bool, float, float> forwardScan();
	std::pair<bool, float> fullScan();
	float* readBeacons(std::string* beaconID, int amount);//return radius
	float readUltrasonic(bool isUlForward);//returns distance in front of node
	float readCompass();
	float readGravityVector();
	float findDistance(float);
	std::string getCommandOutput(std::string cmd, int bytes);
	std::vector<std::string> split(const std::string &s, char delim, std::vector<std::string> &elems);
private:
	std::pair<bool, float> step(int steps, bool isMvForward);
	std::pair<bool, float> foundObject;
	const float pi = 3.141592653;
	const float stepAngle = 5.889;//required
	const float wheelRadius = 0.04075;//required
	const float robotRadius = 0.0825;//required
	const float objDisTolerance = 1;//meters 
	const int turnIncrement = 5;//degrees
	const int power = -12;//dBm ibeacon transmit power
	float wheelCirc;
	float robotCirc;
	float degrees;
	float targetDirection;
	float currentDirection;
	float ultraDist;
	bool isMvForward;
	int stepAmount;
	int steps;
	static mmapGpio gpio;
};
