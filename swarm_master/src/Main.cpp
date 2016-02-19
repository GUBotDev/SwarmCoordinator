#include <thread>
#include "Threading.h"
#include "ros/ros.h"

#include "Write.h"
#include <iostream>
#include <string>

//handle threads only
int main(int argc, char **argv) {
	ros::init(argc, argv, "Master");//, ros::init_options::AnonymousName);
	
	//creates read thread
	std::thread read(&Threading::readThread, Threading());
	read.join();
	
	/*
	Write writer;
	
	
	while(true){
		rosComm.write("All initialize");
		//susleep();
		
		break;
	}
	
	
	for (int i = 0; i < 200; i++){
		writer.write("All initialize");
	}
	*/
	
	

	return 0;
}



