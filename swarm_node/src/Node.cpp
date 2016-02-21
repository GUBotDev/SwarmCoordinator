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
	
	sendPositionDirection(x, y, hardware.readCompass());
	
	lastX = x;
	lastY = y;
	
	busy(false);
}

void Node::turnTo(float targetDirection){
	busy(true);
	
	currentDirection = hardware.readCompass();
	
	angle = targetDirection - currentDirection;
	
	hardware.turn(angle);
	
	busy(false);
}

void Node::locateOne(){//check if area is open
	busy(true);
	
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
	tempPair = hardware.moveForward(yAxis / 10);
	
	baseDirection = hardware.readCompass();
	
	writer.write(ros::this_node::getName() + " is_localized_as 1 " + std::to_string(baseDirection));
	
	busy(false);
}

void Node::locateTwo(float direction){
	busy(true);
	
	//ensure that this faces the same direction as the first when moving starts
	turnTo(direction);
	
	std::pair<bool, float> tempPair;
	std::tuple<bool, float, float> tempTuple;
	float tempDist, tempPosition, tempFoundPosX, tempFoundPosY, targetX, targetY;
	
	tempPair = hardware.moveForward(checkY / 2);
	hardware.turn(-90);
	tempPair = hardware.moveForward(scanDistance / 2);
	hardware.turn(90);
	tempTuple = hardware.forwardScan();
	
	for (int i = 0; i < scanDistance / checkIncrement; i++){
		tempPosition += checkIncrement;//add to X
		
		hardware.turn(90);
		tempPair = hardware.moveForward(checkIncrement);
		hardware.turn(-90);
		tempTuple = hardware.forwardScan();
		
		if (std::get<0>(tempTuple) == true){
			if (tempDist > std::get<1>(tempTuple)){
				tempDist = std::get<1>(tempTuple);
				
				//coordinates relative to starting point of this robot
				tempFoundPosX = sin(std::get<2>(tempTuple)) * tempDist + tempPosition;
				tempFoundPosY = sqrt((tempDist * tempDist) - ((std::get<2>(tempTuple) * tempDist) * (std::get<2>(tempTuple) * tempDist))) + (checkY / 2);
			}
		}
	}
	
	targetX = (scanDistance - tempFoundPosX) + sqrt(((checkY / 10) * (checkY / 10)) - ((checkY / 20) * (checkY / 20)));
	targetY = checkIncrement;
	
	tempPair = hardware.moveBackward(targetX);
	hardware.turn(90);
	hardware.moveBackward(targetY);
	
	writer.write(ros::this_node::getName() + " is_localized_as 2");//
	
	busy(false);
}

void Node::locateThree(std::string beaconIDOne, std::string beaconIDTwo, float direction){//r1, r2, x1, y1, x2, y2
	busy(true);
	
	turnTo(direction);
	
	std::string addresses[2] = { beaconIDOne, beaconIDTwo };
	float x1, x2, y1, y2, x3, y3, tempAngle, tempX, tempY;
	float* radii;
	std::tuple<float, float, float, float> bilateration;
	std::tuple<bool, float, float> tempTuple;
	std::pair<bool, float> tempPair;
	bool isFirst = true;
	
	x1 = sqrt(((checkY / 10) * (checkY / 10)) - (checkIncrement * checkIncrement));
	y1 = -checkIncrement;
	x2 = 0;
	y2 = checkY / 10;
	x3 = -x1;
	y3 = -checkIncrement;
	
	radii = hardware.readBeacons(addresses, 2);
	bilateration = calculate.twoCircleLocate(radii[0], radii[1], x1, x2, y1, y2);
	
	tempAngle = atan2(std::get<2>(bilateration), std::get<0>(bilateration)) * 57.296;
	hardware.turn(tempAngle);
	tempTuple = hardware.forwardScan();
	
	if (!std::get<0>(tempTuple)){
		turnTo(direction);
		tempAngle = atan2(std::get<3>(bilateration), std::get<1>(bilateration)) * 57.296;
		hardware.turn(tempAngle);
		tempTuple = hardware.forwardScan();
		isFirst = false;
		
		tempX = x3 - std::get<1>(bilateration);
		tempY = y3 - std::get<3>(bilateration);
	}
	else{
		tempX = x3 - std::get<0>(bilateration);
		tempY = y3 - std::get<2>(bilateration);
	}
	
	hardware.turn(90);
	
	if (tempX < 0){
		tempPair = hardware.moveBackward(-tempX);
		
		hardware.turn(-90);
		
		if(tempY < 0){
			tempPair = hardware.moveBackward(-tempY);
		}
		else{
			tempPair = hardware.moveForward(tempY);
		}
	}
	else{
		tempPair = hardware.moveForward(tempX);
		
		hardware.turn(-90);
		
		if(tempY < 0){
			tempPair = hardware.moveBackward(-tempY);
		}
		else{
			tempPair = hardware.moveForward(tempY);
		}
	}
	
	writer.write(ros::this_node::getName() + " is_localized_as 3");
	
	busy(false);
}

void Node::busy(bool isBusy){
	writer.write(ros::this_node::getName() + " is_busy " + (isBusy ? "true" : "false"));
}

std::pair<float, float> Node::returnXY(){
	std::pair<float, float> temp;
	
	if (beaconsSet){
		const int amount = numBeacons;
		float* radii;
		
		radii = hardware.readBeacons(beaconID, amount);
		
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
	float currentDir = hardware.readCompass();
	float newX = x + sin(currentDir) * distance;
	float newY = y + cos(currentDir) * distance;	
	
	writer.write(ros::this_node::getName() + " object_found_at " + std::to_string(newX) + " " + std::to_string(newY));
}

void Node::initialize(){
	writer.write(ros::this_node::getName() + " initialize " + (hasBeacon ? ("true " + beaconAddress) : "false "));
}

void Node::sendPositionDirection(float x, float y, bool obstacle){
	float tempAngle = hardware.readCompass();

	writer.write(ros::this_node::getName() + " location_direction " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(tempAngle) + (obstacle ? " true" : " false"));
}

void Node::sendLastPositionDirection(){
	float tempAngle = hardware.readCompass();

	writer.write(ros::this_node::getName() + " location_direction " + std::to_string(lastX) + " " + std::to_string(lastY) + " " + std::to_string(tempAngle) + " false");
}

void Node::alreadyInitialized(){
	writer.write(ros::this_node::getName() + " initialized " + (hasBeacon ? ("true " + beaconAddress) : "false "));
}

void Node::unknownCommand(){
	writer.write(ros::this_node::getName() + " confused");
}



