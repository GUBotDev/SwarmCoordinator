#include "Node.h"

void Node::moveToPosition(float x, float y) {// moves single robot
	isBusy = true;
	newX = x - xPos;
	newY = y - yPos;
	angle = atan2(newY, newX);
	
	hardware.turn(angle);

	distance = sqrt((newX * newX) + (newY * newY));
	
	wasObjectFound = hardware.moveForward(distance);
	
	if (wasObjectFound.first == true){
		
	}
	else{
		
	}
	
	isBusy = false;
}

void Node::locateBeacons(int beacon){
	isBusy = true;
	
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
	
	isBusy = false;
}

void Node::fullScan(){
	float* withinTolerance;
	int numWithinTol = 0;

	for (int i = 0; i < 180 / turnIncrement; i += turnIncrement){
		hardware.turn(i);
		
		float tempFront = hardware.readUltrasonic(true);
		float tempBack = hardware.readUltrasonic(false);
		
		if (tempFront < hardware.objDisTolerance){
			withinTolerance[numWithinTol] = i;
			numWithinTol++;
		}
		
		if (tempBack < hardware.objDisTolerance){
			withinTolerance[numWithinTol] = i + 180;
			numWithinTol++;
		}
	}
	
	hardware.turn(180);
	
	if (numWithinTol > 0){
		std::cout << "Objects found: " << numWithinTol << std::endl << "Objects located at: ";
	
		for (int i = 0; i < numWithinTol; i++){
			std::cout << withinTolerance[i];
		}
		
		std::cout << std::endl;
	}
}

std::pair<bool, float> forwardScan(float angle){
	float* withinTolerance;
	int numWithinTol = 0;

	for (int i = -15; i < 15 / turnIncrement; i += turnIncrement){
		hardware.turn(i);
		
		float tempFront = hardware.readUltrasonic(true);
		
		if (tempFront < hardware.objDisTolerance){
			withinTolerance[numWithinTol] = i;
			numWithinTol++;
		}
		
	}
	
	hardware.turn(180);
	
	if (numWithinTol > 0){
		std::cout << "Objects found: " << numWithinTol << std::endl << "Objects located at: ";
	
		for (int i = 0; i < numWithinTol; i++){
			std::cout << withinTolerance[i];
		}
		
		std::cout << std::endl;
	}
}

void Node::locateOne(){//check if area is open
	float yAxis, xAxisLeft, xAxisRight;
	std::pair<bool, float> tempPair;
	
	tempPair = hardware.moveForward(checkY);//check
	
	if (pair.first == true){
		yAxis = checkY - tempPair.second;
	}
	
	hardware.moveBackward(yAxis / 2);
	hardware.turn(-90);
	tempPair = hardware.moveForward(checkXLeft);//check
	
	if (pair.first == true){
		xAxisLeft = checkXLeft - tempPair.second;
	}
	
	tempPair = hardware.moveBackward(xAxisLeft + checkXRight);//check
	
	if (pair.first == true){
		xAxisRight = checkXRight - tempPair.second;
	}
	
	tempPair = hardware.moveForward(xAxisRight);
	hardware.turn(90);
	tempPair = hardware.moveForward(yAxis / 4);
	
	comm.write("");//node name
}

void Node::locateTwo(){
	//move forward for (yAxis * 3 / 4) / 2
	//move left for xAxisLeft
	//move right for (xAxisLeft + xAxisRight) / 8
	//1 1 1 2 3 4 3 2 - rssi strength
	//0 0 0 0 3 9 3 0 - 
	
	//ensure that this faces the same direction as the first when moving starts
}

void Node::locateThree(){
	
}

