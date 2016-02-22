#include <thread>
#include "Threading.h"
#include "ros/ros.h"

#include "Write.h"
#include "Parse.h"
#include <iostream>
#include <string>
#include <vector>
#include "Movement.h"

//handle threads only
int main(int argc, char **argv) {
	ros::init(argc, argv, "Master", ros::init_options::AnonymousName);
	ros::NodeHandle nhMain;
	//NodeHandler::setNodeHandle(&nhMain);
	//creates read thread
	std::thread read(&Threading::readThread, Threading(), nhMain);
	ros::Publisher publisher;
	publisher = nhMain.advertise<std_msgs::String>("NodeDown", 1000);
	
	Write writer;
	Movement formation;
	writer.initWrite(publisher);
	
	int num;
	
	try{
		while(true){
			std::cout << "Enter int" << std::endl;
			std::cin >> num;
			
			switch(num){
				case 0:
					std::cout << "Initializing nodes... " << std::endl;
					writer.initializeAll();
					break;
				case 1:
					int tempNum;
					
					std::cout << "Choose formation pattern: 0-Inverted V, 1-X, or 2-Diamond" << std::endl;
					std::cin >> tempNum;
					
					formation.setFormation(tempNum);
					break;
				case 2:
					float x, y, dir;
					std::string tempName;
					std::vector<Node> tempNodes = Parse::returnNodes();
					
					std::cout << "Enter name, x/y position and direction" << std::endl;
					
					for (int i = 0; i < tempNodes.size(); i++){
						std::cout << tempNodes[i].getName() << " ";
					}
					
					std::cout << std::endl;
					
					std::cin >> tempName >> x >> y >> dir;
					
					writer.moveToPosition(tempName, x, y, dir);
					break;
			}
		}
	}
	catch(std::exception ex){}
	
	read.join();
	
	return 0;
}



