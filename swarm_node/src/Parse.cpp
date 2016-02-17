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
	
	split(data, ' ', splitMsg);
	
	for (int i = 0; i < splitMsg.size(); i++){
		if (i == 0){
			split(splitMsg[0], '_', splitNode);
		
			//std::cout << splitNode[1] << std::endl;
		}
		else{
			//std::cout << splitMsg[i] << std::endl;
		}
	}
	
	//node_anonymousNum wait - node in position
	
	//node_anonymousNum stop - create new thread and kill when this command is sent
	
	//node_anonymousNum beacon x y x y x y ... - changes the beacon positions for multilateration
	
	//node_anonymousNum 
	
	//node_anonymousNum move x y targetDirection
	x = std::stof(splitMsg[1]);
	y = std::stof(splitMsg[2]);
	targetDirection = std::stof(splitMsg[3]);
	
		
	name = ros::this_node::getName();
		
	split(name, '_', splitName);
		
	if (splitNode[1] == splitName[1]){
		//decHand.decide(x, y, targetDirection);//float x, float y, float targetDirection, float* xBeacons, float* yBeacons, std::string* beaconID, int numBeacons, bool isInFormation
		std::cout << "parseData, add decision handler link" << std::endl;
	}
}

//string to int
//string to float
//string to bool
