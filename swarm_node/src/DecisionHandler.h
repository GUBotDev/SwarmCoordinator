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
	const float positionTolerance = 0.25;//+/- meters
	const float angleTolerance = 10;//+/-degrees
	int numOfBeacons;
	int numOfRobots;
};
