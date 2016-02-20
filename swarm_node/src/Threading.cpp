#include "Threading.h"

Read Threading::rosComm;

void Threading::readThread(ros::NodeHandle nh) {
	while(true){
		try {
			rosComm.read(nh);
		}
		catch (std::exception ex) {
			std::cout << "read thread error" << std::endl;
		}
		
	}
}
