#pragma once

#include <string>
#include <vector>
#include "NodeHandler.h"
#include "Parse.h"
#include "ros/ros.h"
#include "std_msgs/String.h"

class Read {
public:
	void read(ros::NodeHandle nh);
	void readerCallback(const std_msgs::String::ConstPtr& msg);
private:
	Parse parseObj;
	static std::vector<std::string> nodes;
};
