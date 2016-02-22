#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include "Node.h"
#include "Write.h"

class Parse {
public:
	std::vector<std::string> split(const std::string &s, char delim, std::vector<std::string> &elems);
	void parseData(std::string);
	static std::vector<Node> returnNodes();
	void handleInput(int nodeNum, std::vector<std::string> splitMsg, std::string data);
	static float returnBaseDir();
private:
	static std::vector<Node> nodes;
	int beacons;
	std::vector<int> beaconArray;
	Write writer;
	static float baseDirection;
};
