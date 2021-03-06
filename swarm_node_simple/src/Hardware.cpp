#include "Hardware.h"

mmapGpio Hardware::gpio;

std::pair<bool, float> Hardware::moveForward(float meters){
	//meters to steps
	wheelCirc = 2 * pi * wheelRadius;
	robotCirc = 2 * pi * wheelRadius;
	
	steps = meters / ((stepAngle / 360) * wheelCirc);
	
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
	
	steps = meters / ((stepAngle / 360) * wheelCirc);
	
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
		else if (degrees >= 360){
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
			stepAmount = i % 8;

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
			
			usleep(1000);//51.2 mm/s
		}
	}
	else{
		steps *= -1;
		
		int temp = 0;
		
		for (int i = steps; i > 0; i--){
			stepAmount = i % 8;

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
			
			usleep(1000);//51.2 mm/s
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
			stepAmount = i % 8;
			
			//ultraDist = readUltrasonic(isMvForward);
			
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
				
				usleep(1000);//51.2 mm/s
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
			stepAmount = i % 8;

			//ultraDist = readUltrasonic(isMvForward);
			
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
				
				usleep(1000);//51.2 mm/s
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
	int max = 1024;

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
	float expo = (27.55 - (20 * log10(2410)) + abs(intensity) - 32) / 20.0;
	return pow(10, expo);
}

std::vector<float> Hardware::readBeacons(std::string* beaconID, int amount){//return beacon radii
	std::string out;
	
	out = getCommandOutput("hcitool lescan", 256);
	out = getCommandOutput("hcidump", 8096);
	
	int beaconsFound = 0;
	
	std::vector<std::string> splitHCI = split(out, '>');
	std::vector<std::pair<std::string, float>> localRegister;
	std::vector<float> radii;
	
	if (splitHCI.size() == 1024){
		try{
			for (int i = 0; i < splitHCI.size(); i++){
				std::vector<std::string> splitHCIL = split(splitHCI[i], '\n');
			
				if (split(splitHCIL[0], ' ').size() == 9 && splitHCIL.size() > 6){
					//std::cout << splitHCIL[0] << std::endl;
			
					//std::cout << split(splitHCIL[0], ' ')[8] << std::endl;
			
					if ((split(splitHCIL[0], ' ')[8] == "39" && splitHCIL.size() == 8) || (split(splitHCIL[0], ' ')[8] == "42" && splitHCIL.size() == 7)){				
						for (int k = 0; k < amount; k++){
							//std::cout << beaconID[k] << " " << split(splitHCIL[3], ' ')[7] << std::endl;
					
							if (beaconID[k] == split(splitHCIL[3], ' ')[7]){//beacon exists in register
								bool isInLocReg = false;
								int location;
							
								//std::cout << std::to_string(beaconsFound) << std::endl;
							
								for (int j = 0; j < beaconsFound; j++){
									if (localRegister[j].first == split(splitHCIL[3], ' ')[7]){//mac address for beacon is already in register
										isInLocReg = true;
										location = j;
									
										//std::cout << "If J: " << localRegister[j].first << " " << split(splitHCIL[3], ' ')[7] << std::endl;
									
										break;
									}
									else{
										//std::cout << "Else J: " << localRegister[j].first << " " << split(splitHCIL[3], ' ')[7] << std::endl;
									}
								
								}
						
								if (!isInLocReg){//adds to register if not already present
									std::pair<std::string, float> tempPair;
									float temp;
							
									tempPair.first = split(splitHCIL[3], ' ')[7];//add mac to local register
							
									if (split(splitHCIL[0], ' ')[8] == "39"){
										temp = std::stof(split(splitHCIL[7], ' ')[7]);//add rssi to local register
										tempPair.second = findDistance(temp);
									}
									else{
										temp = std::stof(split(splitHCIL[6], ' ')[7]);
										tempPair.second = findDistance(temp);
									}
							
									localRegister.push_back(tempPair);
								
									//std::cout << "localReg: " << std::to_string(tempPair.second) << " " << tempPair.first << std::endl;
								
									beaconsFound++;
								}
								else{
									float temp;
									float tempSec = localRegister[location].second;
							
									if (split(splitHCIL[0], ' ')[8] == "39"){
										temp = std::stof(split(splitHCIL[7], ' ')[7]);
								
										localRegister[location].second = (tempSec + findDistance(temp)) / 2;//add rssi to local register
									}
									else{
										temp = std::stof(split(splitHCIL[6], ' ')[7]);
								
										localRegister[location].second = (tempSec + findDistance(temp)) / 2;//add rssi to local register
									}
								}//end else
							
							}//end if
						}//end for
					}//end if
				}
			}//end for
		
		
			for (int k = 0; k < amount; k++){
				for (int i = 0; i < localRegister.size(); i++){
					if (localRegister[i].first == beaconID[k]){//sorts based on original ordering
						radii.push_back(localRegister[i].second);
					
						//std::cout << "Radii " << std::to_string(radii[k]) << std::endl;
					}
					else{
						//std::cout << std::to_string(k) << std::to_string(i) << std::endl;
					}
				}
			}
			/*
			float* temp = &radii[0];
		
			for (int k = 0; k < localRegister.size(); k++){
				std::cout << localRegister[k].first << " radius: " << std::to_string(temp[k]) << std::endl;
			}
			*/
			std::cout << "-Beacons found." << std::endl;
		
			return radii;
		}
		catch (std::exception ex){
		
		}
	}
	else{
		std::cout << "-Please connect bluetooth device and try again." << std::endl;
		
		return radii;
	}
}

std::vector<std::string> Hardware::split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;

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

