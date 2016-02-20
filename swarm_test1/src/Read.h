#pragma once

#include <string>
#include <vector>
#include "ros/ros.h"
#include "std_msgs/String.h"

class Read {
public:
	void read();
	void readerCallback(const std_msgs::String::ConstPtr& msg);
private:
};
