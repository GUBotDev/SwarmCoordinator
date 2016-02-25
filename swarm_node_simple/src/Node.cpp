#include "Node.h"

Hardware Node::hardware;
Calculation Node::calculate;

void Node::setKnownDirFalse(){
	directionKnown = false;
}

void Node::moveToPosition(float x, float y, float xPos, float yPos) {// moves single robot
	if (!directionKnown){
		correctAngle();
	}

	newX = x - xPos;
	newY = y - yPos;
	angle = atan2(newY, newX);
	
	hardware.turn(angle);

	distance = sqrt((newX * newX) + (newY * newY));
	
	wasObjectFound = hardware.moveForward(distance);
	
	lastX = x;
	lastY = y;
}

void Node::turnTo(float targetDirection){
	//currentDirection = hardware.readCompass();
	
	angle = targetDirection - currentDirection;
	
	hardware.turn(angle);
}

std::pair<float, float> Node::returnXY(){
	std::pair<float, float> temp;
	
	const int amount = numBeacons;
	//float* radii;//[4] = {0.3, 1.8, 1.8, 2.5};
	std::vector<float> radii;
		
	radii = hardware.readBeacons(beaconID, amount);
	
	float* tempRadius = &radii[0];
	
	for (int k = 0; k < amount; k++){
		std::cout << "Radius:" << std::to_string(radii[k]) << " X:" << xBeacons[k] << " Y:" << yBeacons[k] << std::endl;
	}
		
	temp = calculate.multilateration(tempRadius, xBeacons, yBeacons, numBeacons);
	
	std::cout << "Location: " << temp.first << ", " << temp.second << std::endl;
	
	return temp;
}

bool Node::checkTolerances(float x, float y, float xPos, float yPos){
	float tempX = abs(x - xPos);
	float tempY = abs(y - yPos);
	
	if (tempX > positionTolerance || tempY > positionTolerance){
		moveToPosition(x, y, xPos, yPos);
		
		return false;
	}
	else {
		return true;
	}
}

void Node::correctAngle(){
	std::pair<float, float> xy1 = returnXY();
	
	wasObjectFound = hardware.moveForward(checkDistance);

	std::pair<float, float> xy2 = returnXY();

	currentDirection = calculate.determineAngle(xy2.first, xy2.second, xy1.first, xy1.second);
	
	turnTo(0);
}


