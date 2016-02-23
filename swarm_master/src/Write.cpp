#include "Write.h"

void Write::initWrite(ros::Publisher inPublisher){
	publisher = inPublisher;
}

void Write::write(std::string input){
	//ros::NodeHandle nh;// = NodeHandler::returnNodeHandle();

	std_msgs::String msg;
	std::stringstream ss;
	ss << input;
	msg.data = ss.str();
	ROS_INFO("%s", msg.data.c_str());

	publisher.publish(msg);
	ros::spinOnce();
}


void Write::initializeAll(){
	initAllThread();
}

void Write::initAllThread(){
	write("All initialize");
	usleep(50000);
	write("All initialize");
	usleep(50000);
	write("All initialize");
}

void Write::moveToPosition(std::string name, float x, float y, float dir){
	std::string concat = name + " move " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(dir);
	
	write(concat);
}
