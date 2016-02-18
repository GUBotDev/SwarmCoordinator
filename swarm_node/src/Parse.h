#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "ros/ros.h"
#include "DecisionHandler.h"

class Parse {
public:
	std::vector<std::string> split(const std::string &s, char delim, std::vector<std::string> &elems);
	void parseData(std::string);
private:
	int nodeNum;
	bool isWaiting = false;
	std::string name;
	static DecisionHandler decHand;
};
