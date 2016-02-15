#include "DecisionHandler.h"

void DecisionHandler::decide(float x, float y, float targetDirection, float* xBeacons, float* yBeacons, float* beaconID, int numBeacons){
	const int amount = numBeacons;
	float[amount] radius;
	
	radius[0] = ;//use beaconid to associate beacon with position
	radius[1] = ;
	radius[2] = ;
	
	//check tolerance of positioning and angle
	std::pair<float, float> temp = calculate.multilateration(radius, );
	
	node.xPos = temp[0];
	node.yPos = temp[1];
	
	float tempX = x - 
}
