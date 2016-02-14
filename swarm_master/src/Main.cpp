#include <thread>
#include "Threading.h"
#include "ros/ros.h"

//handle threads only
int main(int argc, char **argv) {
	ros::init(argc, argv, "Master");//, ros::init_options::AnonymousName
	
	std::thread read(&Threading::readThread, Threading());
	
	read.join();

	return 0;
}



