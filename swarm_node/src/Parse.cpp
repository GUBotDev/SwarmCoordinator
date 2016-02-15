#include "Parse.h"

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
	
	try{
		split(data, ' ', splitMsg);
	
		for (int i = 0; i < splitMsg.size(); i++){
			if (i == splitMsg.size() - 1){
				split(splitMsg[i], '_', splitNode);
		
				std::cout << splitNode[1] << std::endl;
			
			
			}
			else{
				std::cout << splitMsg[i] << std::endl;
			}
		}
	
		//x y targetDirection node_anonymousNum
		
		x = std::stof(splitMsg[0]);
		y = std::stof(splitMsg[1]);
		targetDirection = std::stof(splitMsg[2]);
		
		name = ros::this_node::getName();
		
		split(name, '_', splitName);
		
		if (splitNode[1] == splitName[1]){
			decHand.decide(x, y, targetDirection);
		}
		
	}
	catch (std::ExceptionName ex){
		std::cout << "Parse error" << std::endl;
	}
}
