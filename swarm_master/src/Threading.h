#pragma once

#include <iostream>
#include <vector>
#include "Read.h"
#include "Parse.h"
#include "ros/ros.h"

class Threading {
public:
	void readThread();
private:
	static Read rosComm;
};
