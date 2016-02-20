#include "NodeHandler.h"

bool NodeHandler::isCreated;
ros::NodeHandle* NodeHandler::nh;

ros::NodeHandle NodeHandler::returnNodeHandle(){
	if(!isCreated){
		ros::NodeHandle nodeHand;
		nh = &nodeHand;
	}
	
	return *nh;
}
