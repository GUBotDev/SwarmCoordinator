#include <thread>
#include "Threading.h"
#include "ros/ros.h"

#include "Write.h"
#include "Parse.h"
#include <iostream>
#include <string>
#include <vector>
#include "NodeHandler.h"

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
					float x, y, dir;
					std::string name;
					std::vector<Node> nodes = Parse::returnNodes();
					
					std::cout << "Enter name, x/y position and direction" << std::endl;
					
					for (int i = 0; i < nodes.size(); i++){
						std::cout << nodes[i].getName() << " ";
					}
					
					std::cout << std::endl;
					
					std::cin >> name >> x >> y >> dir;
					
					writer.moveToPosition(name, x, y, dir);
					break;
			}
		}
	}
	catch(std::exception ex){
	
	}
	
	
	//read.join();
	
	/*
	Write writer;
	
	
	while(true){
		rosComm.write("All initialize");
		//susleep();
		
		break;
	}
	
	
	for (int i = 0; i < 200; i++){
		writer.write("All initialize");
	}
	*/
	
	

	return 0;
}



