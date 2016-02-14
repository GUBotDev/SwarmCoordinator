#pragma once

#include "ros/ros.h"
#include "std_msgs/String.h"

class Communication {
public:
	void read();
	void readerCallback(const std_msgs::String::ConstPtr& msg);
	static ros::NodeHandle nodeHan;
private:
};
