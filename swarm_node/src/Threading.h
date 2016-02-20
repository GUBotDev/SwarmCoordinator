#pragma once

#include <iostream>
#include <vector>
#include "Calculation.h"
#include "Read.h"
#include "Parse.h"
#include "ros/ros.h"

class Threading {
public:
	void readThread(ros::NodeHandle nh);
private:
	static Read rosComm;
};
