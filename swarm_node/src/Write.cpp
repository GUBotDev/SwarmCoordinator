#include "Write.h"

ros::Publisher Write::publisher;

void Write::initWrite(ros::Publisher inPublisher){
	publisher = inPublisher;
}

void Write::write(std::string input){
	std_msgs::String msg;
	std::stringstream ss;
	ss << input;
	msg.data = ss.str();
	ROS_INFO("%s", msg.data.c_str());

	publisher.publish(msg);
	ros::spinOnce();
}
