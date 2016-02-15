#include "Hardware.h"

std::pair<bool, float> Hardware::moveForward(float meters){
	//meters to steps
	wheelCirc = 2 * pi * wheelRadius;
	robotCirc = 2 * pi * wheelRadius;
	
	degrees = (1 / wheelCirc) * 360;
	
	steps = degrees / stepAngle;
	
	//distance left in steps: foundObject.second else false
	foundObject = step(steps, true);
	
	return foundObject;
}

std::pair<bool, float> Hardware::moveBackward(float meters){
	wheelCirc = 2 * pi * wheelRadius;
	robotCirc = 2 * pi * wheelRadius;
	
	degrees = (1 / wheelCirc) * 360;
	
	steps = degrees / stepAngle;
	
	//distance left in steps: foundObject.second else false
	foundObject = step(steps, false);
	
	return foundObject;
}

void Hardware::turn(float targetDirection, float currentDirection){
	degrees = (robotCirc / wheelCirc) * (currentDirection - targetDirection);
	
	steps = degrees / stepAngle;
	
	gpio.setPinDir(0, mmapGpio::OUTPUT);
	gpio.setPinDir(1, mmapGpio::OUTPUT);
	gpio.setPinDir(2, mmapGpio::OUTPUT);
	gpio.setPinDir(3, mmapGpio::OUTPUT);
	gpio.setPinDir(4, mmapGpio::OUTPUT);
	gpio.setPinDir(5, mmapGpio::OUTPUT);
	gpio.setPinDir(6, mmapGpio::OUTPUT);
	gpio.setPinDir(7, mmapGpio::OUTPUT);
	
	if (steps > 0){
		int temp = steps;
		
		for (int i = 0; i < steps; i++){
			step = steps % 8;

			switch (step){
				case 0:
					gpio.writePinLow(0);
					gpio.writePinLow(1);
					gpio.writePinLow(2);
					gpio.writePinHigh(3);
					break;
				case 1:
					gpio.writePinLow(0);
					gpio.writePinLow(1);
					gpio.writePinHigh(2);
					gpio.writePinHigh(3);
					break;
				case 2:
					gpio.writePinLow(0);
					gpio.writePinLow(1);
					gpio.writePinHigh(2);
					gpio.writePinLow(3);
					break;
				case 3:
					gpio.writePinLow(0);
					gpio.writePinHigh(1);
					gpio.writePinHigh(2);
					gpio.writePinLow(3);
					break;
				case 4:
					gpio.writePinLow(0);
					gpio.writePinHigh(1);
					gpio.writePinLow(2);
					gpio.writePinLow(3);
					break;
				case 5:
					gpio.writePinHigh(0);
					gpio.writePinHigh(1);
					gpio.writePinLow(2);
					gpio.writePinLow(3);
					break;
				case 6:
					gpio.writePinHigh(0);
					gpio.writePinLow(1);
					gpio.writePinLow(2);
					gpio.writePinLow(3);
					break;
				case 7:
					gpio.writePinHigh(0);
					gpio.writePinLow(1);
					gpio.writePinLow(2);
					gpio.writePinHigh(3);
					break;
			}
			
			step = temp % 8;
			temp--;
			
			switch (step){
				case 0:
					gpio.writePinLow(4);
					gpio.writePinLow(5);
					gpio.writePinLow(6);
					gpio.writePinHigh(7);
					break;
				case 1:
					gpio.writePinLow(4);
					gpio.writePinLow(5);
					gpio.writePinHigh(6);
					gpio.writePinHigh(7);
					break;
				case 2:
					gpio.writePinLow(4);
					gpio.writePinLow(5);
					gpio.writePinHigh(6);
					gpio.writePinLow(7);
					break;
				case 3:
					gpio.writePinLow(4);
					gpio.writePinHigh(5);
					gpio.writePinHigh(6);
					gpio.writePinLow(7);
					break;
				case 4:
					gpio.writePinLow(4);
					gpio.writePinHigh(5);
					gpio.writePinLow(6);
					gpio.writePinLow(7);
					break;
				case 5:
					gpio.writePinHigh(4);
					gpio.writePinHigh(5);
					gpio.writePinLow(6);
					gpio.writePinLow(7);
					break;
				case 6:
					gpio.writePinHigh(4);
					gpio.writePinLow(5);
					gpio.writePinLow(6);
					gpio.writePinLow(7);
					break;
				case 7:
					gpio.writePinHigh(4);
					gpio.writePinLow(5);
					gpio.writePinLow(6);
					gpio.writePinHigh(7);
					break;
			}
		}
	}
	else{
		steps *= -1;
		
		temp = 0;
		
		for (int i = steps; i > 0; i--){
			step = steps % 8;

			switch (step){
				case 0:
					gpio.writePinLow(0);
					gpio.writePinLow(1);
					gpio.writePinLow(2);
					gpio.writePinHigh(3);
					break;
				case 1:
					gpio.writePinLow(0);
					gpio.writePinLow(1);
					gpio.writePinHigh(2);
					gpio.writePinHigh(3);
					break;
				case 2:
					gpio.writePinLow(0);
					gpio.writePinLow(1);
					gpio.writePinHigh(2);
					gpio.writePinLow(3);
					break;
				case 3:
					gpio.writePinLow(0);
					gpio.writePinHigh(1);
					gpio.writePinHigh(2);
					gpio.writePinLow(3);
					break;
				case 4:
					gpio.writePinLow(0);
					gpio.writePinHigh(1);
					gpio.writePinLow(2);
					gpio.writePinLow(3);
					break;
				case 5:
					gpio.writePinHigh(0);
					gpio.writePinHigh(1);
					gpio.writePinLow(2);
					gpio.writePinLow(3);
					break;
				case 6:
					gpio.writePinHigh(0);
					gpio.writePinLow(1);
					gpio.writePinLow(2);
					gpio.writePinLow(3);
					break;
				case 7:
					gpio.writePinHigh(0);
					gpio.writePinLow(1);
					gpio.writePinLow(2);
					gpio.writePinHigh(3);
					break;
			}
			
			step = temp % 8;
			temp++;
			
			switch (step){
				case 0:
					gpio.writePinLow(4);
					gpio.writePinLow(5);
					gpio.writePinLow(6);
					gpio.writePinHigh(7);
					break;
				case 1:
					gpio.writePinLow(4);
					gpio.writePinLow(5);
					gpio.writePinHigh(6);
					gpio.writePinHigh(7);
					break;
				case 2:
					gpio.writePinLow(4);
					gpio.writePinLow(5);
					gpio.writePinHigh(6);
					gpio.writePinLow(7);
					break;
				case 3:
					gpio.writePinLow(4);
					gpio.writePinHigh(5);
					gpio.writePinHigh(6);
					gpio.writePinLow(7);
					break;
				case 4:
					gpio.writePinLow(4);
					gpio.writePinHigh(5);
					gpio.writePinLow(6);
					gpio.writePinLow(7);
					break;
				case 5:
					gpio.writePinHigh(4);
					gpio.writePinHigh(5);
					gpio.writePinLow(6);
					gpio.writePinLow(7);
					break;
				case 6:
					gpio.writePinHigh(4);
					gpio.writePinLow(5);
					gpio.writePinLow(6);
					gpio.writePinLow(7);
					break;
				case 7:
					gpio.writePinHigh(4);
					gpio.writePinLow(5);
					gpio.writePinLow(6);
					gpio.writePinHigh(7);
					break;
			}
		}
	}
}

std::pair<bool, float> Hardware::step(int steps, bool isMvForward){
	gpio.setPinDir(0, mmapGpio::OUTPUT);
	gpio.setPinDir(1, mmapGpio::OUTPUT);
	gpio.setPinDir(2, mmapGpio::OUTPUT);
	gpio.setPinDir(3, mmapGpio::OUTPUT);
	gpio.setPinDir(4, mmapGpio::OUTPUT);
	gpio.setPinDir(5, mmapGpio::OUTPUT);
	gpio.setPinDir(6, mmapGpio::OUTPUT);
	gpio.setPinDir(7, mmapGpio::OUTPUT);
	
	std::pair<bool, float> tempBoolSteps;
	
	//isMvForward steps -> 0,1,2,3,4,5 else 5,4,3,2,1,0
	if (isMvForward){
		for (int i = 0; i < steps; i++){
			step = steps % 8;
			
			ultraDist = readUltrasonic(isMvForward);
			
			//initialize - overwritten if proved otherwise
			tempBoolSteps.first = false;//no obstacle in path
			tempBoolSteps.second = 0;
				
			if (ultraDist < objDisTolerance){
				switch (step){
					case 0:
						gpio.writePinLow(0);
						gpio.writePinLow(1);
						gpio.writePinLow(2);
						gpio.writePinHigh(3);
					
						gpio.writePinLow(4);
						gpio.writePinLow(5);
						gpio.writePinLow(6);
						gpio.writePinHigh(7);
						break;
					case 1:
						gpio.writePinLow(0);
						gpio.writePinLow(1);
						gpio.writePinHigh(2);
						gpio.writePinHigh(3);
					
						gpio.writePinLow(4);
						gpio.writePinLow(5);
						gpio.writePinHigh(6);
						gpio.writePinHigh(7);
						break;
					case 2:
						gpio.writePinLow(0);
						gpio.writePinLow(1);
						gpio.writePinHigh(2);
						gpio.writePinLow(3);
					
						gpio.writePinLow(4);
						gpio.writePinLow(5);
						gpio.writePinHigh(6);
						gpio.writePinLow(7);
						break;
					case 3:
						gpio.writePinLow(0);
						gpio.writePinHigh(1);
						gpio.writePinHigh(2);
						gpio.writePinLow(3);
					
						gpio.writePinLow(4);
						gpio.writePinHigh(5);
						gpio.writePinHigh(6);
						gpio.writePinLow(7);
						break;
					case 4:
						gpio.writePinLow(0);
						gpio.writePinHigh(1);
						gpio.writePinLow(2);
						gpio.writePinLow(3);
					
						gpio.writePinLow(4);
						gpio.writePinHigh(5);
						gpio.writePinLow(6);
						gpio.writePinLow(7);
						break;
					case 5:
						gpio.writePinHigh(0);
						gpio.writePinHigh(1);
						gpio.writePinLow(2);
						gpio.writePinLow(3);
					
						gpio.writePinHigh(4);
						gpio.writePinHigh(5);
						gpio.writePinLow(6);
						gpio.writePinLow(7);
						break;
					case 6:
						gpio.writePinHigh(0);
						gpio.writePinLow(1);
						gpio.writePinLow(2);
						gpio.writePinLow(3);
					
						gpio.writePinHigh(4);
						gpio.writePinLow(5);
						gpio.writePinLow(6);
						gpio.writePinLow(7);
						break;
					case 7:
						gpio.writePinHigh(0);
						gpio.writePinLow(1);
						gpio.writePinLow(2);
						gpio.writePinHigh(3);
					
						gpio.writePinHigh(4);
						gpio.writePinLow(5);
						gpio.writePinLow(6);
						gpio.writePinHigh(7);
						break;
				}
			}
			else{
				tempBoolSteps.first = true;//obstacle found
				tempBoolSteps.second = i;
				break;
			}
		}
		
		return tempBool;
	}
	else{
		for (int i = steps; i > 0; i--){
			step = steps % 8;

			ultraDist = readUltrasonic(isMvForward);
			
			//initialize - overwritten if object found
			tempBoolSteps.first = false;//no obstacle in path
			tempBoolSteps.second = 0;
				
			if (ultraDist < objDisTolerance){
				switch (step){
					case 0:
						gpio.writePinLow(0);
						gpio.writePinLow(1);
						gpio.writePinLow(2);
						gpio.writePinHigh(3);
					
						gpio.writePinLow(4);
						gpio.writePinLow(5);
						gpio.writePinLow(6);
						gpio.writePinHigh(7);
						break;
					case 1:
						gpio.writePinLow(0);
						gpio.writePinLow(1);
						gpio.writePinHigh(2);
						gpio.writePinHigh(3);
					
						gpio.writePinLow(4);
						gpio.writePinLow(5);
						gpio.writePinHigh(6);
						gpio.writePinHigh(7);
						break;
					case 2:
						gpio.writePinLow(0);
						gpio.writePinLow(1);
						gpio.writePinHigh(2);
						gpio.writePinLow(3);
					
						gpio.writePinLow(4);
						gpio.writePinLow(5);
						gpio.writePinHigh(6);
						gpio.writePinLow(7);
						break;
					case 3:
						gpio.writePinLow(0);
						gpio.writePinHigh(1);
						gpio.writePinHigh(2);
						gpio.writePinLow(3);
					
						gpio.writePinLow(4);
						gpio.writePinHigh(5);
						gpio.writePinHigh(6);
						gpio.writePinLow(7);
						break;
					case 4:
						gpio.writePinLow(0);
						gpio.writePinHigh(1);
						gpio.writePinLow(2);
						gpio.writePinLow(3);
					
						gpio.writePinLow(4);
						gpio.writePinHigh(5);
						gpio.writePinLow(6);
						gpio.writePinLow(7);
						break;
					case 5:
						gpio.writePinHigh(0);
						gpio.writePinHigh(1);
						gpio.writePinLow(2);
						gpio.writePinLow(3);
					
						gpio.writePinHigh(4);
						gpio.writePinHigh(5);
						gpio.writePinLow(6);
						gpio.writePinLow(7);
						break;
					case 6:
						gpio.writePinHigh(0);
						gpio.writePinLow(1);
						gpio.writePinLow(2);
						gpio.writePinLow(3);
					
						gpio.writePinHigh(4);
						gpio.writePinLow(5);
						gpio.writePinLow(6);
						gpio.writePinLow(7);
						break;
					case 7:
						gpio.writePinHigh(0);
						gpio.writePinLow(1);
						gpio.writePinLow(2);
						gpio.writePinHigh(3);
					
						gpio.writePinHigh(4);
						gpio.writePinLow(5);
						gpio.writePinLow(6);
						gpio.writePinHigh(7);
						break;
				}
			}
			else{
				tempBoolSteps.first = true;//obstacle found
				tempBoolSteps.second = i;
				
				break;
			}
		}
		
		return tempBool;
	}
}


float* Hardware::readBeacons(std::string name){//return beacon radii

}

float Hardware::readUltrasonic(){//return distance in meters

}

float Hardware::readCompass(){//return angle from north

}

float Hardware::readGravityVector(){

}

