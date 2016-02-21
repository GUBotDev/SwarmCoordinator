#pragma once

#include <string>
#include <tuple>
#include "Write.h"

class Node {
public:
	std::string getName();
	std::string getMac();
	void setName(std::string);
	void handleInput(std::string data);
	void setBeacon(bool);
	void setBusy(bool);
	void localizeOne();
	void localizeTwo(float baseDir);
	void localizeThree(std::string macOne, std::string macTwo, float baseDir);
	std::tuple<float, float, std::string> returnXYMac();
	
private:
	std::string name;
	std::string macAdd;
	bool hasBeacon;
	bool isBusy;
	float x;
	float y;
	Write writer;
};
