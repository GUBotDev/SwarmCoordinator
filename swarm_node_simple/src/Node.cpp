#include "Node.h"

Hardware Node::hardware;
Calculation Node::calculate;

void Node::moveToPosition(float x, float y, float xPos, float yPos) {// moves single robot
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
	currentDirection = hardware.readCompass();
	
	angle = targetDirection - currentDirection;
	
	hardware.turn(angle);
}

std::pair<float, float> Node::returnXY(){
	std::pair<float, float> temp;
	
	if (beaconsSet){
		const int amount = numBeacons;
		float* radii;
		
		radii = hardware.readBeacons(beaconID, amount);
		
		temp = calculate.multilateration(radii, xBeacons, yBeacons, numBeacons);
	}
	
	return temp;
}

void Node::checkTolerances(float targetDirection){
	if (hardware.readCompass() > (targetDirection + angleTolerance) || hardware.readCompass() < (targetDirection - angleTolerance)){
		turnTo(targetDirection);
	}
}

void Node::checkTolerances(float x, float y, float xPos, float yPos){
	float tempX = abs(x - xPos);
	float tempY = abs(y - yPos);
	
	if (tempX > positionTolerance || tempY > positionTolerance){
		moveToPosition(x, y, xPos, yPos);
	}
}




