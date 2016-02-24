#include <thread>
#include "Threading.h"
#include "ros/ros.h"
#include "Write.h"

//handle threads only
int main(int argc, char **argv) {
	ros::init(argc, argv, "Node", ros::init_options::AnonymousName);
	ros::NodeHandle nh;
	ros::Publisher publisherMain;
	
	publisherMain = nh.advertise<std_msgs::String>("NodeUp", 1000);
	
	//creates read thread
	std::thread read(&Threading::readThread, Threading(), nh);
	
	Write writer;
	
	writer.initWrite(publisherMain);
	
	
	
	/*
	Write rosComm;
	
	while(true){
		//x y compass ultrasonic node_anonymousNum
		rosComm.write("12.5 -16 175.4 24 Node_012345678");
		rosComm.write("0.3 23.5 130.3 253 Node_123456789");
		rosComm.write("-26.3 34.5 60.2 0 Node_234567890");
	}
	*/
	
	read.join();

	return 0;
}



