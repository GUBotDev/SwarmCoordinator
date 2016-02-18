#include "Node.h"

Hardware Node::hardware;
Write Node::writer;
Calculation Node::calculate;

void Node::moveToPosition(float x, float y, float xPos, float yPos) {// moves single robot
	busy(true);
	
	newX = x - xPos;
	newY = y - yPos;
	angle = atan2(newY, newX);
	
	hardware.turn(angle);

	distance = sqrt((newX * newX) + (newY * newY));
	
	wasObjectFound = hardware.moveForward(distance);
	
	if (wasObjectFound.first == true){
		//FORMATION SHIFT COURSE - send command to master to redirect
		objectFound(x, y, wasObjectFound.second);
	}
	
	sendPositionDirection(x, y, wasObjectFound.first);
	
	busy(false);
}

void Node::locateBeacons(int beacon){
	busy(true);
	
	switch (beacon){
		case 0:
			locateOne();
			break;
		case 1:
			locateTwo();
			break;
		case 2:
			locateThree();
			break;
	}
	
	busy(false);
}

void Node::turnTo(float targetDirection){
	currentDirection = hardware.readCompass();
	
	angle = targetDirection - currentDirection;
	
	hardware.turn(angle);
}

void Node::locateOne(){//check if area is open
	float yAxis, xAxisLeft, xAxisRight;
	std::pair<bool, float> tempPair;
	
	tempPair = hardware.moveForward(checkY);//check
	
	if (tempPair.first == true){
		yAxis = checkY - tempPair.second;
	}
	
	hardware.moveBackward(yAxis / 2);
	hardware.turn(-90);
	tempPair = hardware.moveForward(checkXLeft);//check
	
	if (tempPair.first == true){
		xAxisLeft = checkXLeft - tempPair.second;
	}
	
	tempPair = hardware.moveBackward(xAxisLeft + checkXRight);//check
	
	if (tempPair.first == true){
		xAxisRight = checkXRight - tempPair.second;
	}
	
	tempPair = hardware.moveForward(xAxisRight);
	hardware.turn(90);
	tempPair = hardware.moveForward(yAxis / 4);
	
	baseDirection = hardware.readCompass();
	
	writer.write(ros::this_node::getName() + " is_localized_as 1 " + std::to_string(xAxisLeft + xAxisRight) + " " + std::to_string(yAxis) + " " + std::to_string(baseDirection));
}

void Node::locateTwo(){
	//move forward for (yAxis * 3 / 4) / 2
	//move left for xAxisLeft
	//move right for (xAxisLeft + xAxisRight) / 8
	//1 1 1 2 3 4 3 2 - rssi strength
	//0 0 0 0 3 9 3 0 - 
	
	//ensure that this faces the same direction as the first when moving starts
	std::tuple<bool, float, float> tempTuple = hardware.forwardScan();
	
	
	writer.write(ros::this_node::getName() + " is_localized_as 2");
}

void Node::locateThree(){
	
	writer.write(ros::this_node::getName() + " is_localized_as 3");
}

void Node::busy(bool isBusy){
	writer.write(ros::this_node::getName() + " is_busy " + (isBusy ? "true" : "false"));
}

std::pair<float, float> Node::returnXY(){
	std::pair<float, float> temp;
	
	if (beaconsSet){
		const int amount = numBeacons;
		float radii[amount];
	
		for (int i = 0; i < amount; i++){
			radii[i] = hardware.readBeacons(beaconID[i]);
		}
	
		temp = calculate.multilateration(radii, xBeacons, yBeacons, numBeacons);
	}
	else{
		requestBeacons();
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

void Node::requestBeacons(){
	writer.write(ros::this_node::getName() + " request_beacons");
}

void Node::setBeacons(float* xBeacons, float* yBeacons, std::string* ID, int numBeacons){
	this->xBeacons = xBeacons;
	this->yBeacons = yBeacons;
	this->beaconID = ID;
	this->numBeacons = numBeacons;
}

void Node::objectFound(float x, float y, float distance){
	float tempPos = distance * sin(baseDirection);
	
	writer.write(ros::this_node::getName() + " object_found_at " + std::to_string(tempPos));
}

void Node::initialize(){
	writer.write(ros::this_node::getName() + " initialize " + (hasBeacon ? "true" : "false"));
}

void Node::sendPositionDirection(float x, float y, bool obstacle){
	float tempAngle = hardware.readCompass();

	writer.write(ros::this_node::getName() + " location_direction " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(tempAngle) + (obstacle ? " true" : " false"));
}

void Node::alreadyInitialized(){
	writer.write(ros::this_node::getName() + " initialized " + (hasBeacon ? "true" : "false"));
}

void Node::unknownCommand(){
	writer.write(ros::this_node::getName() + " confused");
}



