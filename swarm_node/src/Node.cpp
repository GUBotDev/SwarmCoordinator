#include "Node.h"

void Node::moveToPosition(float x, float y) {// moves single robot
	isBusy = true;
	newX = x - xPos;
	newY = y - yPos;
	angle = atan2(newY, newX);
	
	moveNode.turn(angle);

	distance = sqrt((newX * newX) + (newY * newY));
	
	wasObjectFound = moveNode.moveForward(distance);
	
	if (wasObjectFound.first == true){
		
	}
	else{
		
	}
	
	isBusy = false;
}

void Node::locateBeacons(int beacon){
	switch (beacon){
		case 0:
			locateOne();
			break;
		case 1:
			locateTwo();
			break;
		case 2;
			locateThree();
			break;
	}
}

void Node::fullScan(){
	for (int i = 0; i < 360; i += turnIncrements){
		moveNode.turn(5);
		
	}
}

void Node::locateOne(){

}

void Node::locateTwo(){

}

void Node::locateThree(){

}

