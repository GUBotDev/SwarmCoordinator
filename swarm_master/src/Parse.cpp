#include "Parse.h"

std::vector<std::string> Parse::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim)) {

        elems.push_back(item);

    }

    return elems;
}

void parseData(std::string data){
	std::vector<std::string> splitMsg;
	std::vector<std::string> splitNode;
	
	parseObj.split(data, ' ', splitMsg);
	
	for (int i = 0; i < splitMsg.size(); i++){
		
		if (i == splitMsg.size() - 1){
			parseObj.split(splitMsg[i], '_', splitNode);
		
			std::cout << splitNode[1] << std::endl;
			
			
		}
		else{
			std::cout << splitMsg[i] << std::endl;
		}
	}

}
