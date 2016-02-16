#include "DecisionHandler.h"

void DecisionHandler::decide(float x, float y, float targetDirection, float* xBeacons, float* yBeacons, std::string* beaconID, int numBeacons, bool isInFormation){
	const int amount = numBeacons;
	float[amount] radii;
	
	radii[1] = ;
	radii[2] = ;
	
	for (int i = 0; i < amount; i++){
		radii[i] = node.hardware.readBeacons(beaconID[i]);
	}
	
	//check tolerance of positioning and angle
	std::pair<float, float> temp = calculate.multilateration(radii, xBeacons, yBeacons, numBeacons);
	
	node.xPos = temp[0];
	node.yPos = temp[1];
	
	float tempX = abs(x - node.xPos);
	float tempY = abs(y - node.yPos);
	
	if (tempX > positionTolerance || tempY > positionTolerance){
		//shift position
		
	}
	
	if (node.hardware.readCompass() > (targetDirection + angleTolerance) || node.hardware.readCompass() < (targetDirection - angleTolerance)){
		//shift angle
		
	}
}
