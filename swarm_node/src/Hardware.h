#pragma once

#include <cmath>
#include <array>
#include <vector>
#include "mmapGpio.h"
#include "stdio.h"

class Hardware {
public:
	void turn(float targetDirection);
	std::pair<bool, float> moveForward(float meters);
	std::pair<bool, float> moveBackward(float meters);
	float readBeacons(std::string name);//return radius
	float readUltrasonic(bool isUlForward);//returns distance in front of node
	float readCompass();
	float readGravityVector();
	const float objDisTolerance = 0.2;//meters 
	mmapGpio gpio;
private:
	std::pair<bool, float> step(int steps, bool isMvForward);
	std::pair<bool, float> foundObject;
	const float pi = 3.141592653;
	const float stepAngle = 5.889;//required
	const float wheelRadius = 0.04075;//required
	const float robotRadius = 0.0825;//required
	float wheelCirc;
	float robotCirc;
	float degrees;
	float targetDirection;
	float currentDirection;
	float ultraDist;
	bool isMvForward;
	int stepAmount;
	int steps;
};
