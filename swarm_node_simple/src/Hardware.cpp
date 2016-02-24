#include "Hardware.h"

mmapGpio Hardware::gpio;

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

std::pair<bool, float> Hardware::fullScan(){
	float* withinTolerance;
	int numWithinTol = 0;
	float tempDist = 5;
	std::pair<bool, float> temp;

	for (int i = 0; i < 180 / turnIncrement; i += turnIncrement){
		turn(i);
		
		float tempFront = readUltrasonic(true);
		float tempBack = readUltrasonic(false);
		
		if (tempFront < objDisTolerance){
			withinTolerance[numWithinTol] = i;
			numWithinTol++;
			
			if (tempDist > tempFront){
				tempDist = tempFront;
			}
		}
		
		if (tempBack < objDisTolerance){
			withinTolerance[numWithinTol] = i + 180;
			numWithinTol++;
			
			if (tempDist > tempBack){
				tempDist = tempBack;
			}
		}
	}
	
	turn(180);
	
	if (numWithinTol > 0){
		std::cout << "Objects found: " << numWithinTol << std::endl << "Objects located at: ";
	
		for (int i = 0; i < numWithinTol; i++){
			std::cout << withinTolerance[i];
		}
		
		std::cout << std::endl;
		
		temp.first = true;
		temp.second = tempDist;
	}
	else{
		temp.first = false;
		temp.second = 0;
	}
}

std::tuple<bool, float, float> Hardware::forwardScan(){
	float* withinTolerance;
	int numWithinTol = 0;
	float tempDist = 5;
	float tempAngle;
	std::tuple<bool, float, float> temp;

	for (int i = -15; i < 15 / turnIncrement; i += turnIncrement){
		turn(i);
		
		float tempFront = readUltrasonic(true);
		
		if (tempFront < objDisTolerance){
			withinTolerance[numWithinTol] = i;
			numWithinTol++;
			
			if (tempDist > tempFront){
				tempDist = tempFront;
				tempAngle = i;
			}
		}
	}
	
	turn(-15);
	
	if (numWithinTol > 0){
		std::cout << "Objects found: " << numWithinTol << std::endl << "Objects located at: ";
	
		for (int i = 0; i < numWithinTol; i++){
			std::cout << withinTolerance[i];
		}
		
		std::cout << std::endl;
		
		std::make_tuple(true, tempDist, tempAngle);
	}
	else{
		std::make_tuple(false, 0, 0);
	}
	
	return temp;
}


void Hardware::turn(float angle){
	currentDirection = readCompass();

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
	
	int pin0 = 2;
	int pin1 = 3; 
	int pin2 = 4;
	int pin3 = 5;
	int pin4 = 6;
	int pin5 = 13;
	int pin6 = 19;
	int pin7 = 26;
	
	gpio.setPinDir(pin0, mmapGpio::OUTPUT);
	gpio.setPinDir(pin1, mmapGpio::OUTPUT);
	gpio.setPinDir(pin2, mmapGpio::OUTPUT);
	gpio.setPinDir(pin3, mmapGpio::OUTPUT);
	gpio.setPinDir(pin4, mmapGpio::OUTPUT);
	gpio.setPinDir(pin5, mmapGpio::OUTPUT);
	gpio.setPinDir(pin6, mmapGpio::OUTPUT);
	gpio.setPinDir(pin7, mmapGpio::OUTPUT);
	
	if (steps > 0){
		int temp = steps;
		
		for (int i = 0; i < steps; i++){
			stepAmount = steps % 8;

			switch (stepAmount){
				case 0:
					gpio.writePinLow(pin0);
					gpio.writePinLow(pin1);
					gpio.writePinLow(pin2);
					gpio.writePinHigh(pin3);
					break;
				case 1:
					gpio.writePinLow(pin0);
					gpio.writePinLow(pin1);
					gpio.writePinHigh(pin2);
					gpio.writePinHigh(pin3);
					break;
				case 2:
					gpio.writePinLow(pin0);
					gpio.writePinLow(pin1);
					gpio.writePinHigh(pin2);
					gpio.writePinLow(pin3);
					break;
				case 3:
					gpio.writePinLow(pin0);
					gpio.writePinHigh(pin1);
					gpio.writePinHigh(pin2);
					gpio.writePinLow(pin3);
					break;
				case 4:
					gpio.writePinLow(pin0);
					gpio.writePinHigh(pin1);
					gpio.writePinLow(pin2);
					gpio.writePinLow(pin3);
					break;
				case 5:
					gpio.writePinHigh(pin0);
					gpio.writePinHigh(pin1);
					gpio.writePinLow(pin2);
					gpio.writePinLow(pin3);
					break;
				case 6:
					gpio.writePinHigh(pin0);
					gpio.writePinLow(pin1);
					gpio.writePinLow(pin2);
					gpio.writePinLow(pin3);
					break;
				case 7:
					gpio.writePinHigh(pin0);
					gpio.writePinLow(pin1);
					gpio.writePinLow(pin2);
					gpio.writePinHigh(pin3);
					break;
			}
			
			stepAmount = temp % 8;
			temp--;
			
			switch (stepAmount){
				case 0:
					gpio.writePinLow(pin4);
					gpio.writePinLow(pin5);
					gpio.writePinLow(pin6);
					gpio.writePinHigh(pin7);
					break;
				case 1:
					gpio.writePinLow(pin4);
					gpio.writePinLow(pin5);
					gpio.writePinHigh(pin6);
					gpio.writePinHigh(pin7);
					break;
				case 2:
					gpio.writePinLow(pin4);
					gpio.writePinLow(pin5);
					gpio.writePinHigh(pin6);
					gpio.writePinLow(pin7);
					break;
				case 3:
					gpio.writePinLow(pin4);
					gpio.writePinHigh(pin5);
					gpio.writePinHigh(pin6);
					gpio.writePinLow(pin7);
					break;
				case 4:
					gpio.writePinLow(pin4);
					gpio.writePinHigh(pin5);
					gpio.writePinLow(pin6);
					gpio.writePinLow(pin7);
					break;
				case 5:
					gpio.writePinHigh(pin4);
					gpio.writePinHigh(pin5);
					gpio.writePinLow(pin6);
					gpio.writePinLow(pin7);
					break;
				case 6:
					gpio.writePinHigh(pin4);
					gpio.writePinLow(pin5);
					gpio.writePinLow(pin6);
					gpio.writePinLow(pin7);
					break;
				case 7:
					gpio.writePinHigh(pin4);
					gpio.writePinLow(pin5);
					gpio.writePinLow(pin6);
					gpio.writePinHigh(pin7);
					break;
			}
			
			usleep(82000);//51.2 mm/s
		}
	}
	else{
		steps *= -1;
		
		int temp = 0;
		
		for (int i = steps; i > 0; i--){
			stepAmount = steps % 8;

			switch (stepAmount){
				case 0:
					gpio.writePinLow(pin0);
					gpio.writePinLow(pin1);
					gpio.writePinLow(pin2);
					gpio.writePinHigh(pin3);
					break;
				case 1:
					gpio.writePinLow(pin0);
					gpio.writePinLow(pin1);
					gpio.writePinHigh(pin2);
					gpio.writePinHigh(pin3);
					break;
				case 2:
					gpio.writePinLow(pin0);
					gpio.writePinLow(pin1);
					gpio.writePinHigh(pin2);
					gpio.writePinLow(pin3);
					break;
				case 3:
					gpio.writePinLow(pin0);
					gpio.writePinHigh(pin1);
					gpio.writePinHigh(pin2);
					gpio.writePinLow(pin3);
					break;
				case 4:
					gpio.writePinLow(pin0);
					gpio.writePinHigh(pin1);
					gpio.writePinLow(pin2);
					gpio.writePinLow(pin3);
					break;
				case 5:
					gpio.writePinHigh(pin0);
					gpio.writePinHigh(pin1);
					gpio.writePinLow(pin2);
					gpio.writePinLow(pin3);
					break;
				case 6:
					gpio.writePinHigh(pin0);
					gpio.writePinLow(pin1);
					gpio.writePinLow(pin2);
					gpio.writePinLow(pin3);
					break;
				case 7:
					gpio.writePinHigh(pin0);
					gpio.writePinLow(pin1);
					gpio.writePinLow(pin2);
					gpio.writePinHigh(pin3);
					break;
			}
			
			stepAmount = temp % 8;
			temp++;
			
			switch (stepAmount){
				case 0:
					gpio.writePinLow(pin4);
					gpio.writePinLow(pin5);
					gpio.writePinLow(pin6);
					gpio.writePinHigh(pin7);
					break;
				case 1:
					gpio.writePinLow(pin4);
					gpio.writePinLow(pin5);
					gpio.writePinHigh(pin6);
					gpio.writePinHigh(pin7);
					break;
				case 2:
					gpio.writePinLow(pin4);
					gpio.writePinLow(pin5);
					gpio.writePinHigh(pin6);
					gpio.writePinLow(pin7);
					break;
				case 3:
					gpio.writePinLow(pin4);
					gpio.writePinHigh(pin5);
					gpio.writePinHigh(pin6);
					gpio.writePinLow(pin7);
					break;
				case 4:
					gpio.writePinLow(pin4);
					gpio.writePinHigh(pin5);
					gpio.writePinLow(pin6);
					gpio.writePinLow(pin7);
					break;
				case 5:
					gpio.writePinHigh(pin4);
					gpio.writePinHigh(pin5);
					gpio.writePinLow(pin6);
					gpio.writePinLow(pin7);
					break;
				case 6:
					gpio.writePinHigh(pin4);
					gpio.writePinLow(pin5);
					gpio.writePinLow(pin6);
					gpio.writePinLow(pin7);
					break;
				case 7:
					gpio.writePinHigh(pin4);
					gpio.writePinLow(pin5);
					gpio.writePinLow(pin6);
					gpio.writePinHigh(pin7);
					break;
			}
			
			usleep(82000);//51.2 mm/s
		}
	}
}

std::pair<bool, float> Hardware::step(int steps, bool isMvForward){
	int pin0 = 2;
	int pin1 = 3; 
	int pin2 = 4;
	int pin3 = 5;
	int pin4 = 6;
	int pin5 = 13;
	int pin6 = 19;
	int pin7 = 26;

	gpio.setPinDir(pin0, mmapGpio::OUTPUT);
	gpio.setPinDir(pin1, mmapGpio::OUTPUT);
	gpio.setPinDir(pin2, mmapGpio::OUTPUT);
	gpio.setPinDir(pin3, mmapGpio::OUTPUT);
	gpio.setPinDir(pin4, mmapGpio::OUTPUT);
	gpio.setPinDir(pin5, mmapGpio::OUTPUT);
	gpio.setPinDir(pin6, mmapGpio::OUTPUT);
	gpio.setPinDir(pin7, mmapGpio::OUTPUT);
	
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
						gpio.writePinLow(pin0);
						gpio.writePinLow(pin1);
						gpio.writePinLow(pin2);
						gpio.writePinHigh(pin3);
					
						gpio.writePinLow(pin4);
						gpio.writePinLow(pin5);
						gpio.writePinLow(pin6);
						gpio.writePinHigh(pin7);
						break;
					case 1:
						gpio.writePinLow(pin0);
						gpio.writePinLow(pin1);
						gpio.writePinHigh(pin2);
						gpio.writePinHigh(pin3);
					
						gpio.writePinLow(pin4);
						gpio.writePinLow(pin5);
						gpio.writePinHigh(pin6);
						gpio.writePinHigh(pin7);
						break;
					case 2:
						gpio.writePinLow(pin0);
						gpio.writePinLow(pin1);
						gpio.writePinHigh(pin2);
						gpio.writePinLow(pin3);
					
						gpio.writePinLow(pin4);
						gpio.writePinLow(pin5);
						gpio.writePinHigh(pin6);
						gpio.writePinLow(pin7);
						break;
					case 3:
						gpio.writePinLow(pin0);
						gpio.writePinHigh(pin1);
						gpio.writePinHigh(pin2);
						gpio.writePinLow(pin3);
					
						gpio.writePinLow(pin4);
						gpio.writePinHigh(pin5);
						gpio.writePinHigh(pin6);
						gpio.writePinLow(pin7);
						break;
					case 4:
						gpio.writePinLow(pin0);
						gpio.writePinHigh(pin1);
						gpio.writePinLow(pin2);
						gpio.writePinLow(pin3);
					
						gpio.writePinLow(pin4);
						gpio.writePinHigh(pin5);
						gpio.writePinLow(pin6);
						gpio.writePinLow(pin7);
						break;
					case 5:
						gpio.writePinHigh(pin0);
						gpio.writePinHigh(pin1);
						gpio.writePinLow(pin2);
						gpio.writePinLow(pin3);
					
						gpio.writePinHigh(pin4);
						gpio.writePinHigh(pin5);
						gpio.writePinLow(pin6);
						gpio.writePinLow(pin7);
						break;
					case 6:
						gpio.writePinHigh(pin0);
						gpio.writePinLow(pin1);
						gpio.writePinLow(pin2);
						gpio.writePinLow(pin3);
					
						gpio.writePinHigh(pin4);
						gpio.writePinLow(pin5);
						gpio.writePinLow(pin6);
						gpio.writePinLow(pin7);
						break;
					case 7:
						gpio.writePinHigh(pin0);
						gpio.writePinLow(pin1);
						gpio.writePinLow(pin2);
						gpio.writePinHigh(pin3);
					
						gpio.writePinHigh(pin4);
						gpio.writePinLow(pin5);
						gpio.writePinLow(pin6);
						gpio.writePinHigh(pin7);
						break;
				}
				
				usleep(82000);//51.2 mm/s
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
						gpio.writePinLow(pin0);
						gpio.writePinLow(pin1);
						gpio.writePinLow(pin2);
						gpio.writePinHigh(pin3);
					
						gpio.writePinLow(pin4);
						gpio.writePinLow(pin5);
						gpio.writePinLow(pin6);
						gpio.writePinHigh(pin7);
						break;
					case 1:
						gpio.writePinLow(pin0);
						gpio.writePinLow(pin1);
						gpio.writePinHigh(pin2);
						gpio.writePinHigh(pin3);
					
						gpio.writePinLow(pin4);
						gpio.writePinLow(pin5);
						gpio.writePinHigh(pin6);
						gpio.writePinHigh(pin7);
						break;
					case 2:
						gpio.writePinLow(pin0);
						gpio.writePinLow(pin1);
						gpio.writePinHigh(pin2);
						gpio.writePinLow(pin3);
					
						gpio.writePinLow(pin4);
						gpio.writePinLow(pin5);
						gpio.writePinHigh(pin6);
						gpio.writePinLow(pin7);
						break;
					case 3:
						gpio.writePinLow(pin0);
						gpio.writePinHigh(pin1);
						gpio.writePinHigh(pin2);
						gpio.writePinLow(pin3);
					
						gpio.writePinLow(pin4);
						gpio.writePinHigh(pin5);
						gpio.writePinHigh(pin6);
						gpio.writePinLow(pin7);
						break;
					case 4:
						gpio.writePinLow(pin0);
						gpio.writePinHigh(pin1);
						gpio.writePinLow(pin2);
						gpio.writePinLow(pin3);
					
						gpio.writePinLow(pin4);
						gpio.writePinHigh(pin5);
						gpio.writePinLow(pin6);
						gpio.writePinLow(pin7);
						break;
					case 5:
						gpio.writePinHigh(pin0);
						gpio.writePinHigh(pin1);
						gpio.writePinLow(pin2);
						gpio.writePinLow(pin3);
					
						gpio.writePinHigh(pin4);
						gpio.writePinHigh(pin5);
						gpio.writePinLow(pin6);
						gpio.writePinLow(pin7);
						break;
					case 6:
						gpio.writePinHigh(pin0);
						gpio.writePinLow(pin1);
						gpio.writePinLow(pin2);
						gpio.writePinLow(pin3);
					
						gpio.writePinHigh(pin4);
						gpio.writePinLow(pin5);
						gpio.writePinLow(pin6);
						gpio.writePinLow(pin7);
						break;
					case 7:
						gpio.writePinHigh(pin0);
						gpio.writePinLow(pin1);
						gpio.writePinLow(pin2);
						gpio.writePinHigh(pin3);
					
						gpio.writePinHigh(pin4);
						gpio.writePinLow(pin5);
						gpio.writePinLow(pin6);
						gpio.writePinHigh(pin7);
						break;
				}
				
				usleep(82000);//51.2 mm/s
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

std::string Hardware::getCommandOutput(std::string cmd, int bytes) {
	std::string data;
	FILE * stream;
	const int max_buffer = bytes;
	char buffer[max_buffer];
	cmd.append(" 2>&1");
	int count = 0;
	int max = 128;

	stream = popen(cmd.c_str(), "r");
	
	if (stream) {	
		while (!feof(stream) && count < max){
			if (fgets(buffer, max_buffer, stream) != NULL){
				data.append(buffer);
			}
			
			count++;
		}
		
		//pclose(stream);
	}

	return data;
}

float Hardware::findDistance(float intensity){
	float expo = (27.55 - (20 * log10(2410)) + abs(intensity) - 45) / 20.0;
	return pow(10, expo);
}

float* Hardware::readBeacons(std::string* beaconID, int amount){//return beacon radii
	std::string out;
	
	out = getCommandOutput("hcitool lescan", 256);
	out = getCommandOutput("hcidump", 8096);
	
	int beaconsFound = 0;
	
	std::vector<std::string> splitHCIEvent;
	std::vector<std::string> splitHCIEventLine;
	std::vector<std::string> splitHCIEventLineData;
	std::vector<std::pair<std::string, float>> localRegister;
	std::vector<int> localRegisterAvgNums;
	float* radii;
	
	try{
		split(out, '>', splitHCIEvent);
	
		for (int i = 0; i < splitHCIEvent.size(); i++){
			split(splitHCIEvent[i], '\n', splitHCIEventLine);
		
			split(splitHCIEventLine[0], ' ', splitHCIEventLineData);
		
			if (splitHCIEventLineData[7] == "39" && splitHCIEventLine.size() == 8){
				split(splitHCIEventLine[3], ' ', splitHCIEventLineData);
				
				for (int k = 0; k < amount; k++){
					if (beaconID[k] == splitHCIEventLineData[1]){//beacon exists in register
						if (beaconsFound == 0){// local beacon list is empty
							localRegister[beaconsFound].first = splitHCIEventLineData[1];//add mac to local register
							
							split(splitHCIEventLine[7], ' ', splitHCIEventLineData);
							
							localRegister[beaconsFound].second = std::stof(splitHCIEventLineData[1]);//add rssi to local register
							
							if (localRegisterAvgNums[beaconsFound] == 0){
								localRegisterAvgNums[beaconsFound] = 0;
							}
							else{
								localRegisterAvgNums[beaconsFound]++;
							}
							
							beaconsFound++;
						}
						else{
							bool isInLocReg = false;
							int location;
							
							for (int j = 0; j < beaconsFound; j++){
								if (localRegister[j].first == splitHCIEventLineData[1]){//mac address for beacon is already in register
									isInLocReg == true;
									location = j;
								}
							}
							
							if (!isInLocReg){//adds to register if not already present
								localRegister[beaconsFound].first = splitHCIEventLineData[1];//add mac to local register
							
								split(splitHCIEventLine[7], ' ', splitHCIEventLineData);
							
								localRegister[beaconsFound].second = std::stof(splitHCIEventLineData[1]);//add rssi to local register
							}
							else{
								split(splitHCIEventLine[7], ' ', splitHCIEventLineData);
							
								localRegister[location].second += std::stof(splitHCIEventLineData[1]);//add rssi to local register
								
								
								if (localRegisterAvgNums[beaconsFound] == 0){
									localRegisterAvgNums[beaconsFound] = 0;
								}
								else{
									localRegisterAvgNums[beaconsFound]++;
								}//end else
							}//end else
						}//end else
					}//end if
				}//end for
			}//end if
		}//end for
		
		for (int i = 0; i < localRegister.size(); i++){
			for (int k = 0; k < amount; k++){
				if (localRegister[i].first == beaconID[k]){//sorts based on original ordering
					radii[k] = findDistance(localRegister[i].second / localRegisterAvgNums[i]);
				}
			}
		}
	}
	catch (std::exception ex){
	
	}
}

std::vector<std::string> Hardware::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }

    return elems;
}

float Hardware::readUltrasonic(bool isUlForward){//return distance in meters
	int pin = 21;
	
	//ping
	gpio.setPinDir(pin, mmapGpio::OUTPUT);
	gpio.writePinLow(pin);
	usleep(2000);//microseconds
	gpio.writePinHigh(pin);
	usleep(5000);
	gpio.writePinLow(pin);
	
	//pong
	gpio.setPinDir(pin, mmapGpio::INPUT);
	gpio.writePinHigh(pin);
	
	auto timeInit = Clock::now();
	int temp = 0;
	
	while(gpio.readPin(pin) == 0){
		if (temp > 1000000){
			break;//prevent infinite loop
		}
		
		temp++;
	}
	
	auto timePost = Clock::now();
	long tempMicroSeconds = std::chrono::duration_cast<std::chrono::nanoseconds>(timeInit - timePost).count() * 1000;//nano to mico
	float distance = (tempMicroSeconds / 5813.8);//time to distance
	
	return distance;
}

float Hardware::readCompass(){//return degrees from north
	return 0;
}

float Hardware::readGravityVector(){
	return 0;
}

