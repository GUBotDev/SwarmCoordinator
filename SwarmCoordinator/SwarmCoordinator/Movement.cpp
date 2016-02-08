#include "Movement.h"


void Movement::setFormation(int formation, ControllerNode controller) {
	//designate relative position for each robot
	switch (formation) {
	case 0:
		invertedV(controller);
		break;
	case 1:
		cross(controller);
		break;
	case 2:
		square(controller);
		break;
	}
}

void Movement::invertedV(ControllerNode controller) {
	float pos;

	if (controller.numOfBots % 2 == 1) {//odd number of robots
		controller.numOfBots -= 1;

		for (int i = 0; i < controller.numOfBots / 2; i++) {
			pos = i / 10;

			controller.bots[i].moveToPosition(-pos, -pos);
			controller.bots[i + 1].moveToPosition(pos, -pos);
		}
		
		controller.bots[controller.numOfBots].moveToPosition(0, -pos);
	}
	else {
		for (int i = 0; i < controller.numOfBots / 2; i++) {
			pos = i / 10;

			controller.bots[i].moveToPosition(-pos, -pos);
			controller.bots[i + 1].moveToPosition(pos, -pos);
		}
	}
}

void Movement::cross(ControllerNode controller) {

}

void Movement::square(ControllerNode controller) {

}

// ^
// X
// T
// diamond
// square
// rotate formation

/*
0
	0.1m per text block
			A
		  1   2
		3       4
	  5           6
	7               8
	// degree "a" depends on if walls are found
1
	1               2
	  3           4
		5       6
		  7   8
			A
		  9  10
		11      13
	  14          15
	16              17
2
	3   1   A   2   4

	5               6

	7               8

	9   11  13  12  10

*/