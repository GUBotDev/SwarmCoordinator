#pragma once

#include <string>
#include <vector>
#include <sstream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <unistd.h>

class Write {
public:
	void initWrite(ros::Publisher inPublisher);
	void write(std::string);
	void initializeAll();
	void moveToPosition(std::string name, float x, float y, float dir);
	void initAllThread();
private:
	static ros::Publisher publisher;
};
