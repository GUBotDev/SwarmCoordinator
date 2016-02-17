#include "Write.h"

void Write::write(std::string input){
	ros::NodeHandle nodeHand;
	ros::Publisher publisher;
	
	publisher = nodeHand.advertise<std_msgs::String>("NodeUp", 1000);

	std_msgs::String msg;
	std::stringstream ss;
	ss << input;
	msg.data = ss.str();
	ROS_INFO("%s", msg.data.c_str());

	publisher.publish(msg);
	ros::spinOnce();
}
