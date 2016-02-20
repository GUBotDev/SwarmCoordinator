#pragma once

#include <string>

class Node {
public:
	std::string getName();
	void setName(std::string);
	void handleInput(std::string data);
	void setBeacon(bool);
	void setBusy(bool);
private:
	std::string name;
	std::string macAdd;
	bool hasBeacon;
	bool isBusy;
};
