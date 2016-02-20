#include "Write.h"

void Write::write(std::string input){
	ros::NodeHandle nh = NodeHandler::returnNodeHandle();
	ros::Publisher publisher;
	
	publisher = nh.advertise<std_msgs::String>("NodeDown", 1000);

	std_msgs::String msg;
	std::stringstream ss;
	ss << input;
	msg.data = ss.str();
	ROS_INFO("%s", msg.data.c_str());

	publisher.publish(msg);
	ros::spinOnce();
}

void Write::initializeAll(){
	//initAllThread();
	
	write("All initialize");
}

void Write::moveToPosition(std::string name, float x, float y, float dir){
	std::string concat = name + " " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(dir);
	
	//write(concat);
}

void Write::initAllThread(){
	//write("All initialize", nodeHand);
	usleep(50000);
}
