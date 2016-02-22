#include "Parse.h"

std::vector<Node> Parse::nodes;
float Parse::baseDirection;
//void handleInput(in);

std::vector<Node> Parse::returnNodes(){
	return nodes;
}

std::vector<std::string> Parse::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim)){

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
				handleInput(i, splitMsg, data);
			}
			else{
				int tempInt = nodes.size() + 1;
				
				nodes[tempInt] = tempNode;
				nodes[tempInt].setName(splitMsg[0]);
				
				handleInput(tempInt, splitMsg, data);
			}
		}
	}
}

void Parse::handleInput(int nodeNum, std::vector<std::string> splitMsg, std::string data){
	if (splitMsg[1] == "initialize"){
		if (splitMsg[2] == "true"){
			nodes[nodeNum].setBeacon(true);
			nodes[nodeNum].setAddress(splitMsg[3]);
			
			beaconArray[beacons] = nodeNum;
				
			if (beacons == 0){
				nodes[nodeNum].localizeOne();
			}
			
			beacons++;
		}
		else{
			nodes[nodeNum].setBeacon(false);
		}
	}
	else if (splitMsg[1] == "request_beacons"){
		std::tuple<float, float, std::string> tempTuple;
		std::string tempConcat = "All beacons " + std::to_string(beaconArray.size());
		
		for (int i = 0; i < beaconArray.size(); i++){
			tempTuple = nodes[nodeNum].returnXYMac();
			
			tempConcat += " " + std::to_string(std::get<0>(tempTuple)) + " " + std::to_string(std::get<1>(tempTuple)) + " " + std::get<2>(tempTuple);
		}
		
		writer.write(tempConcat);
	}
	else if (splitMsg[1] == "object_found_at"){
		//handle change in formation
		
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
		if (std::stoi(splitMsg[2]) == 1){
			baseDirection = std::stof(splitMsg[3]);
			//localize 2
			nodes[beaconArray[1]].localizeTwo(baseDirection);
		}
		else if (std::stoi(splitMsg[2]) == 2){
			//localize 3
			nodes[beaconArray[2]].localizeThree(nodes[beaconArray[0]].getMac(), nodes[beaconArray[1]].getMac(), baseDirection);
			beacons++;
		}
		else if (std::stoi(splitMsg[2]) == 3){
			std::cout << "Localization complete." << std::endl;
			beacons++;
		}
		else{
			std::cout << "Master is confused." << std::endl;
		}
	}
	else if (splitMsg[1] == "location_direction"){
		nodes[nodeNum].setXYD(std::stof(splitMsg[2]), std::stof(splitMsg[3]), std::stof(splitMsg[4]));
		
		if (splitMsg[5] == "true"){
			//obstacle handling
			
		}
	}
	else if (splitMsg[1] == "initialized"){
		if (splitMsg[2] == "true"){
			nodes[nodeNum].setBeacon(true);
			nodes[nodeNum].setAddress(splitMsg[3]);
			
			if (beacons == 0){
				beaconArray[beacons] = nodeNum;
				
				nodes[nodeNum].localizeOne();
			
				beacons++;
			}
			
			std::string concat = nodes[nodeNum].getName() + " initialized";
			
			writer.write(concat);
		}
		else{
			nodes[nodeNum].setBeacon(false);
		}
	}
	else if (splitMsg[1] == "confused_about"){
		std::vector<std::string> splitData;
		std::vector<std::string> splitErrMsg;
	
		split(data, ' ', splitData);
		split(splitData[1], ' ', splitErrMsg);
		
		//splitErrMsg is original message that was sent and returned
	}
	else{
		std::cout << "Master is confused." << std::endl;
	}
}

float Parse::returnBaseDir(){
	return baseDirection;
}

