#include "Hardware.h"

std::pair<bool, float> Hardware::moveForward(float meters){
	//meters to steps
	wheelCirc = 2 * pi * wheelRadius;
	robotCirc = 2 * pi * wheelRadius;
	
	degrees = (1 / wheelCirc) * 360;
	
	steps = degrees / stepAngle;
	
	//distance left in steps: foundObject.second else false
	foundObject = step(steps, true);
	
	if (foundObject.first == true){
		float tempMeters = 1 / ((foundObject.second * stepAngle) / 360);
		
		foundObject.second = tempMeters;
	}
	
	return foundObject;
}

std::pair<bool, float> Hardware::moveBackward(float meters){
	wheelCirc = 2 * pi * wheelRadius;
	robotCirc = 2 * pi * wheelRadius;
	
	degrees = (1 / wheelCirc) * 360;
	
	steps = degrees / stepAngle;
	
	//distance left in steps: foundObject.second else false
	foundObject = step(steps, false);
	
	if (foundObject.first == true){
		float tempMeters = 1 / ((foundObject.second * stepAngle) / 360);
		
		foundObject.second = tempMeters;
	}
	
	return foundObject;
}

void Hardware::turn(float angle){
	//currentDirection = 

	targetDirection = angle + currentDirection;
	degrees = (robotCirc / wheelCirc) * (targetDirection - currentDirection);
	
	//shortest turning angle
	if (abs(degrees) > 180){
		if (degrees < 0){
			degrees += 360;
		}
		else{
			degrees -= 360;
		}
	}
	
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
			stepAmount = steps % 8;

			switch (stepAmount){
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
			
			stepAmount = temp % 8;
			temp--;
			
			switch (stepAmount){
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
		
		int temp = 0;
		
		for (int i = steps; i > 0; i--){
			stepAmount = steps % 8;

			switch (stepAmount){
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
			
			stepAmount = temp % 8;
			temp++;
			
			switch (stepAmount){
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
			stepAmount = steps % 8;
			
			ultraDist = readUltrasonic(isMvForward);
			
			//initialize - overwritten if proved otherwise
			tempBoolSteps.first = false;//no obstacle in path
			tempBoolSteps.second = 0;
				
			if (ultraDist < objDisTolerance){
				switch (stepAmount){
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
		
		return tempBoolSteps;
	}
	else{
		for (int i = steps; i > 0; i--){
			stepAmount = steps % 8;

			ultraDist = readUltrasonic(isMvForward);
			
			//initialize - overwritten if object found
			tempBoolSteps.first = false;//no obstacle in path
			tempBoolSteps.second = 0;
				
			if (ultraDist < objDisTolerance){
				switch (stepAmount){
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
		
		return tempBoolSteps;
	}
}


float Hardware::readBeacons(std::string name){//return beacon radii

}

float Hardware::readUltrasonic(bool isUlForward){//return distance in meters

}

float Hardware::readCompass(){//return angle from north

}

float Hardware::readGravityVector(){

}

