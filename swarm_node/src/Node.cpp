#include "Node.h"

Hardware Node::hardware;
Write Node::writer;

void Node::moveToPosition(float x, float y) {// moves single robot
	busy(true);
	
	newX = x - xPos;
	newY = y - yPos;
	angle = atan2(newY, newX);
	
	hardware.turn(angle);

	distance = sqrt((newX * newX) + (newY * newY));
	
	wasObjectFound = hardware.moveForward(distance);
	
	if (wasObjectFound.first == true){
		//FORMATION SHIFT COURSE - send command to master to stop and redirect
	}
	
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
	
	writer.write(std::string("NodeOneLocalized ") + std::string(ros::this_node::getName()) + " " + std::to_string(yAxis) + " " + std::to_string(xAxisLeft) + " " + std::to_string(xAxisRight));//node name, xleft, xright, y
}

void Node::locateTwo(){
	//move forward for (yAxis * 3 / 4) / 2
	//move left for xAxisLeft
	//move right for (xAxisLeft + xAxisRight) / 8
	//1 1 1 2 3 4 3 2 - rssi strength
	//0 0 0 0 3 9 3 0 - 
	
	//ensure that this faces the same direction as the first when moving starts
	
	writer.write("NodeTwoLocalized ");
}

void Node::locateThree(){
	writer.write("NodeThreeLocalized ");
}

void Node::busy(bool isBusy){
	writer.write(std::string("Busy") + std::string(ros::this_node::getName()) + std::string(isBusy));
}


