#include "Parse.h"

std::vector<Node> Parse::nodes;
//void handleInput(in);

std::vector<Node> Parse::returnNodes(){
	return nodes;
}

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
	Node tempNode;
	
	split(data, ' ', splitMsg);
	
	for (int i = 0; i < splitMsg.size(); i++){
		for (int i = 0; i < nodes.size(); i++){
			if (nodes[i].getName() == splitMsg[0]){
				handleInput(i, splitMsg);
			}
			else{
				int tempInt = nodes.size() + 1;
				
				nodes[tempInt] = tempNode;
				nodes[tempInt].setName(splitMsg[0]);
				
				nodes[tempInt].handleInput(data);
				
				handleInput(tempInt, splitMsg);
			}
		}
	}
}

void Parse::handleInput(int nodeNum, std::vector<std::string> splitMsg){
	if (splitMsg[1] == "initialize"){
		if (splitMsg[2] == "true"){
			nodes[nodeNum].setBeacon(true);
		}
		else{
			nodes[nodeNum].setBeacon(false);
		}
	}
	else if (splitMsg[1] == "request_beacons"){
		
	}
	else if (splitMsg[1] == "object_found_at"){
		
	}
	else if (splitMsg[1] == "is_busy"){
		if (splitMsg[2] == "true"){
			nodes[nodeNum].setBusy(true);
		}
		else{
			nodes[nodeNum].setBusy(false);
		}
	}
	else if (splitMsg[1] == "is_localized_as"){
	
	}
	else if (splitMsg[1] == "location"){
	
	}
	else if (splitMsg[1] == "initialized"){
		if (splitMsg[2] == "true"){
			nodes[nodeNum].setBeacon(true);
		}
		else{
			nodes[nodeNum].setBeacon(false);
		}
	}
	else{
		std::cout << "Master is confused." << std::endl;
	}
}



