#include "Communication.h"

ros::NodeHandle Communication::nodeHan;

void Communication::readerCallback(const std_msgs::String::ConstPtr& msg){
	//ROS_INFO("[%s]", msg->data.c_str());
	std::cout << "test" << std::endl;
}

void Communication::read(){
	ros::Subscriber reader;
	reader = nodeHan.subscribe("tester", 1000, &Communication::readerCallback, this);
			
	ros::spin();
}
