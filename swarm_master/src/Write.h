#pragma once

#include <string>
#include <vector>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <unistd.h>

class Write {
public:
	void write(std::string);
	void initializeAll();
	void moveToPosition(std::string name, float x, float y, float dir);
	void initAllThread();
private:

};
