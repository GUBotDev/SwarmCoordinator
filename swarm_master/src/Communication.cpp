#include "Communication.h"

//ros::NodeHandle Communication::nodeHan;
Parse Communication::parseObj;
DecisionHandler Communication::decHand;

void Communication::readerCallback(const std_msgs::String::ConstPtr& msg){
	//ROS_INFO("input: [%s]", msg->data.c_str());
	
	parseObj.parseData(msg->data.c_str());
}

void Communication::read(){
	ros::NodeHandle nodeHan;
	ros::Subscriber reader;
	
	reader = nodeHan.subscribe("tester", 1000, &Communication::readerCallback, this);
			
	ros::spin();
}

void Communication::write(std::string input){
	ros::NodeHandle nodeHand;
	ros::Publisher publisher;
	
	publisher = nodeHand.advertise<std_msgs::String>("tester", 1000);


	std_msgs::String msg;
	std::stringstream ss;
	ss << input;
	msg.data = ss.str();
	ROS_INFO("%s", msg.data.c_str());

	publisher.publish(msg);
	ros::spinOnce();
}
