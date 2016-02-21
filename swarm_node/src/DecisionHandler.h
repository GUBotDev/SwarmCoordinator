#pragma once

#include <string>
#include <thread>
#include "Node.h"

class DecisionHandler {
public:
	void setBeacons(float* x, float* y, std::string* ID, int numBeacons);
	void move(float x, float y);
	void turn(float targetDirection);
	void localize(int num, float direction, std::string macOne, std::string macTwo);
	void initialize();
	void initComplete();
	bool isInit();
	void alreadyInitialized();
	void sendPosDir();
	void unknownCommand();
private:
	bool initComp = false;
	bool beaconsInitialized = false;
	static Node node;
};
