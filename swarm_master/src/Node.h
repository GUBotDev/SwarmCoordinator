#pragma once

#include <string>

class Node {
public:
	std::string getName();
	void handleInput(std::string data);
private:
	std::string name;
	std::string macAdd;
};
