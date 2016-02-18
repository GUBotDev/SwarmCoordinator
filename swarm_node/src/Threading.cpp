#include "Threading.h"

Read Threading::rosComm;

void Threading::readThread() {
	while(true){
		try {
			rosComm.read();
		}
		catch (std::exception ex) {
			std::cout << "read thread error" << std::endl;
		}
		
	}
}
