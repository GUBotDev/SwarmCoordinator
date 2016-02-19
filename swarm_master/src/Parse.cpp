#include "Parse.h"

std::vector<Node> Parse::nodes;

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
				
			}
			else{
				int tempInt = nodes.size() + 1;
				nodes[tempInt] = tempNode;
				nodes[tempInt].getName() = splitMsg[0];
				
				nodes[tempInt].handleInput(data);
			}
		}
	}
	
}
