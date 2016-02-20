#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "NodeHandler.h"

class Write {
public:
	void write(std::string);
	void initializeAll();
	void moveToPosition(std::string name, float x, float y, float dir);
	void initAllThread();
private:
	//static ros::NodeHandle nodeHand;
	bool isHand = false;
	//NodeHandler nHR;
};
