#pragma once

#include <string>
#include "Node.h"
#include "Calculation.h"

class DecisionHandler {
public:
	void decide(float x, float y, float targetDirection);
private:
	Node node;
	Calculation calculate;
	float directionTolerance = 0.25;//+/- meters
	float angleTolerance = 10;//+/-degrees
	int numOfBeacons;
	int numOfRobots;
};
