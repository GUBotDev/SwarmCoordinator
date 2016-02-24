#include "Node.h"

//handle threads only
int main(int argc, char **argv) {
	while (true){
		int input;
		std::pair<float, float> tempPos;
		Node node;
		
		std::cout << "Enter command" << std::endl;
	
		std::cin >> input;
		
		switch (input){
			case 0:
				//
				std::cout << "Enter position" << std::endl;
				
				float x, y;
				
				std:: cin >> x >> y;
				
				tempPos = node.returnXY();
				node.moveToPosition(x, y, tempPos.first, tempPos.second);
				node.checkTolerances(x, y, tempPos.first, tempPos.second);
				
				break;
			case 1:
				//
				
				break;
			case 2:
				//
				
				break;
			case 3:
				//
				
				break;
			case 4:
				//
				
				break;
		}
	}
	
	return 0;
}



