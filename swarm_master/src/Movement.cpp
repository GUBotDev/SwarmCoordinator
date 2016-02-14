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
		diamond(controller);
		break;
	}
}

void Movement::invertedV(ControllerNode controller) {
	float pos;

	if (controller.numOfBots % 2 == 1) {//odd number of robots
		int bots = controller.numOfBots - 1;

		for (int i = 0; i < bots; i += 2) {
			pos = i / 10;//to change scaling change the divisor

			controller.bots[i].moveToPosition(-pos, -pos);
			controller.bots[i + 1].moveToPosition(pos, -pos);
		}

		controller.bots[controller.numOfBots].moveToPosition(0, -pos);
	}
	else {
		for (int i = 0; i < controller.numOfBots; i += 2) {
			pos = i / 10;

			controller.bots[i].moveToPosition(-pos, -pos);
			controller.bots[i + 1].moveToPosition(pos, -pos);
		}
	}
}

void Movement::cross(ControllerNode controller) {//X
	float pos;

	if (controller.numOfBots % 2 == 1) {
		int bots = controller.numOfBots - 1;

		pos = controller.numOfBots / 10;

		for (int i = 0; i < bots; i += 2) {
			controller.bots[i].moveToPosition(-pos, pos);
			controller.bots[i + 1].moveToPosition(pos, pos);

			pos -= 0.1;
		}
	}
	else {
		pos = controller.numOfBots / 10;

		for (int i = 0; i < controller.numOfBots; i += 2) {
			controller.bots[i].moveToPosition(-pos, pos);
			controller.bots[i + 1].moveToPosition(pos, pos);

			pos -= 0.1;
		}
	}
}

void Movement::diamond(ControllerNode controller) {
	float pos;
	float pos2;

	if (controller.numOfBots % 2 == 1) {
		int bots = controller.numOfBots - 1;
		int halfBots = controller.numOfBots / 2;

		for (int i = 0; i < bots; i += 2) {
			pos = i / 10;//to change scaling change the divisor

			if (i <= halfBots) {
				controller.bots[i].moveToPosition(-pos, -pos);
				controller.bots[i + 1].moveToPosition(pos, -pos);

				pos2 = pos;
			}
			else if (i == controller.numOfBots) {
				controller.bots[controller.numOfBots].moveToPosition(-pos, -pos);
			}
			else {
				pos2 -= 1 / 10;

				controller.bots[i].moveToPosition(-pos2, -pos);
				controller.bots[i + 1].moveToPosition(pos2, -pos);
			}
		}
	}
	else {
		int halfBots = controller.numOfBots / 2;

		for (int i = 0; i < controller.numOfBots; i += 2) {
			pos = i / 10;//to change scaling change the divisor

			if (i <= halfBots) {
				controller.bots[i].moveToPosition(-pos, -pos);
				controller.bots[i + 1].moveToPosition(pos, -pos);

				pos2 = pos;
			}
			else {
				pos2 -= 1 / 10;

				controller.bots[i].moveToPosition(-pos2, -pos);
				controller.bots[i + 1].moveToPosition(pos2, -pos);
			}
		}
	}

}

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
			A
		  1   2
		3       4
	  5           6
	7               8
	  3           4
		5       6
		  7   8
			9

*/