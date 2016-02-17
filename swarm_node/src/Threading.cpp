#include "Threading.h"

//DecisionHandler Parse::decHand;
Read Threading::rosComm;

void Threading::readThread() {
	//Read rosComm;
	
	while(true){
		try {
			rosComm.read();
			
			//break;
		}
		catch (std::exception ex) {
			std::cout << "read thread error" << std::endl;
		}
		
	}
}
