#include "Parse.h"

DecisionHandler Parse::decHand;

std::vector<std::string> Parse::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }

    return elems;
}

void Parse::parseData(std::string data){
	std::vector<std::string> splitMsg;
	std::vector<std::string> splitNode;
	std::vector<std::string> splitName;
		
	name = ros::this_node::getName();
	
	split(data, ' ', splitMsg);
	split(splitMsg[0], '_', splitNode);
	split(name, '_', splitName);
		
	if (splitNode[1] == splitName[1] || splitMsg[0] == "All"){
		//node_anonymousNum wait - node in position
		//****node_anonymousNum stop - create new thread and kill when this command is sent - release mutexes/semaphores, free dynamic memory (nope)
		//node_anonymousNum beacons numB x y id x y id x y id... - changes the beacon positions for multilateration
		//node_anonymousNum turn direction
		//node_anonymousNum move x y
		//node_anonymousNum localize num
		if (splitMsg[1] == "wait"){
			if (isWaiting == false){
				std::cout << name << " waiting..." << std::endl;
				isWaiting = true;
			}
		}
		else if (splitMsg[1] == "initialize" && !decHand.isInit()){
			decHand.initialize();
		}
		else if (splitMsg[1] == "initialize" && decHand.isInit()){
			//say that this node has been initialized
			decHand.alreadyInitialized();
		}
		else if (splitMsg[1] == "initialized"){
			decHand.initComplete();
		}
		else if (splitMsg[1] == "beacons"){
			isWaiting = false;
			
			float* tempX;
			float* tempY;
			std::string* tempID;
			int tempBeacons = std::stoi(splitMsg[2]);
			
			for (int i = 3; i < splitMsg.size(); i += 3){
				tempX[i] = std::stof(splitMsg[i]);
				tempY[i] = std::stof(splitMsg[i + 1]);
				tempID[i] = splitMsg[i + 2];
			}
			
			decHand.setBeacons(tempX, tempY, tempID, tempBeacons);
		}
		else if (splitMsg[1] == "turn"){
			isWaiting = false;
			
			float tempTargetDirection = std::stof(splitMsg[2]);
			
			decHand.turn(tempTargetDirection);
		}
		else if (splitMsg[1] == "move"){
			isWaiting = false;
			
			float tempX = std::stof(splitMsg[2]);
			float tempY = std::stof(splitMsg[3]);
			
			decHand.move(tempX, tempY);
		}
		else if (splitMsg[1] == "localize"){
			isWaiting = false;
			
			int tempNum = std::stoi(splitMsg[2]);
			
			decHand.localize(tempNum);//, xAxis, yAxis, );
		}
		else{
			decHand.unknownCommand();
		}
	}
}
