#include "Threading.h"

void Threading::readThread() {
	Communication rosComm;
	
	while(true){
		try {
			rosComm.read();
		}
		catch (std::exception ex) {
			std::cout << "read thread error" << std::endl;
		}
		
	}
}

/*

	std::pair<float, float> position;
	std::vector<std::string> nodeList;
	Calculation calcObj;
	Parse parseObj;

			float degree;
			float radius[3] = { 15, 5, 6 };
			float x[3] = { -10, 0, 10 };//static x positions
			float y[3] = { -10, 10, -10 };//static y positions

			position = calcObj.multilateration(radius, x, y, 3);

			degree = calcObj.determineAngle(position.first, position.second, 0, 0);

			std::cout << "X: " << position.first << " Y: " << position.second << " deg: " << degree << std::endl;
		
		
		

*/
