#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "ros/ros.h"
#include "std_msgs/String.h"

class NodeHandler {
public:
	static ros::NodeHandle returnNodeHandle();
private:
	static bool isCreated;
	static ros::NodeHandle* nh;
};
