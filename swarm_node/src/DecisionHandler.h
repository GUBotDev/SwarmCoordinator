#pragma once

#include <string>
#include "Node.h"
#include "Calculation.h"

class DecisionHandler {
public:
	void decide(float x, float y, float targetDirection, float* xBeacons, float* yBeacons, std::string* beaconID, int numBeacons, bool isInFormation);
private:
	static Node node;
	static Calculation calculate;
	const float positionTolerance = 0.25;//+/- meters
	const float angleTolerance = 10;//+/-degrees
	int numOfBeacons;
	int numOfRobots;
};
