#pragma once

#include <string>
#include <vector>
#include "ros/ros.h"
#include "std_msgs/String.h"

class Write {
public:
	void initWrite(ros::Publisher inPublisher);
	void write(std::string);
private:
	static ros::Publisher publisher;
};
