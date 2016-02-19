#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include "Node.h"

class Parse {
public:
	std::vector<std::string> split(const std::string &s, char delim, std::vector<std::string> &elems);
	void parseData(std::string);
private:
	static std::vector<Node> splitNode;
};
