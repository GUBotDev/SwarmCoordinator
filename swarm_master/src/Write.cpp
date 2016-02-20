#include "Write.h"

void Write::write(std::string input){
	ros::NodeHandle nodeHand;
	ros::Publisher publisher;
	
	publisher = nodeHand.advertise<std_msgs::String>("NodeDown", 1000);

	std_msgs::String msg;
	std::stringstream ss;
	ss << input;
	msg.data = ss.str();
	ROS_INFO("%s", msg.data.c_str());

	publisher.publish(msg);
	ros::spinOnce();
}

void Write::initializeAll(){
	auto initAllThread();
}

void Write::moveToPosition(std::string name, float x, float y, float dir){
	std::string concat = name + " " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(dir);
	
	write(concat);
}

void Write::initAllThread(){
	write("All initialize");
	usleep(50000);
	write("All initialize");
	usleep(50000);
	write("All initialize");
}
