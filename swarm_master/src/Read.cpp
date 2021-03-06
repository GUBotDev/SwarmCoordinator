#include "Read.h"

//Parse Communication::parseObj;
//DecisionHandler Communication::decHand;

void Read::readerCallback(const std_msgs::String::ConstPtr& msg){
	ROS_INFO("input: [%s]", msg->data.c_str());
	
	//parse to find orders
	parseObj.parseData(msg->data.c_str());
}

void Read::read(ros::NodeHandle nh){
	//ros::NodeHandle nh;// = NodeHandler::returnNodeHandle();
	ros::Subscriber reader;
	
	reader = nh.subscribe("NodeUp", 1000, &Read::readerCallback, this);
			
	ros::spin();
}
