#pragma once

#include <string>
#include <vector>
#include "Parse.h"
#include "DecisionHandler.h"
#include "ros/ros.h"
#include "std_msgs/String.h"

class Communication {
public:
	void read();
	void readerCallback(const std_msgs::String::ConstPtr& msg);
	void write(std::string);
private:
	static Parse parseObj;
	static DecisionHandler decHand;
	static std::vector<std::string> nodes;
};
