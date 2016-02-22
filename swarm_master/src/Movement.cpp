#include "Movement.h"


void Movement::setFormation(int formation) {
	nodes = Parse::returnNodes();
	baseDirection = Parse::returnBaseDir();

	//designate relative position for each robot
	switch (formation) {
		case 0:
			invertedV();
			break;
		case 1:
			xPattern();
			break;
		case 2:
			diamond();
			break;
	}
}

void Movement::invertedV() {
	float pos;

	if (nodes.size() % 2 == 1) {//odd number of robots
		int num = nodes.size() - 1;

		for (int i = 0; i < num; i += 2) {
			pos = i / 5;//to change scaling change the divisor

			nodes[i].moveToPosition(-pos, -pos, baseDirection);
			nodes[i + 1].moveToPosition(pos, -pos, baseDirection);
		}

		nodes[num + 1].moveToPosition(0, -pos, baseDirection);
	}
	else {
		for (int i = 0; i < nodes.size(); i += 2) {
			pos = i / 5;

			nodes[i].moveToPosition(-pos, -pos, baseDirection);
			nodes[i + 1].moveToPosition(pos, -pos, baseDirection);
		}
	}
}

void Movement::xPattern() {//X
	float pos;

	if (nodes.size() % 2 == 1) {
		int num = nodes.size() - 1;

		pos = nodes.size() / 5;

		for (int i = 0; i < num; i += 2) {
			nodes[i].moveToPosition(-pos, pos, baseDirection);
			nodes[i + 1].moveToPosition(pos, pos, baseDirection);

			pos -= 0.2;
		}
	}
	else {
		pos = nodes.size() / 5;

		for (int i = 0; i < nodes.size(); i += 2) {
			nodes[i].moveToPosition(-pos, pos, baseDirection);
			nodes[i + 1].moveToPosition(pos, pos, baseDirection);

			pos -= 0.2;
		}
	}
}

void Movement::diamond() {
	float pos;
	float pos2;

	if (nodes.size() % 2 == 1) {
		int num = nodes.size() - 1;
		int halfNum = nodes.size() / 2;

		for (int i = 0; i < num; i += 2) {
			pos = i / 10;//to change scaling change the divisor

			if (i <= halfNum) {
				nodes[i].moveToPosition(-pos, -pos, baseDirection);
				nodes[i + 1].moveToPosition(pos, -pos, baseDirection);

				pos2 = pos;
			}
			else if (i == nodes.size()) {
				nodes[num + 1].moveToPosition(-pos, -pos, baseDirection);
			}
			else {
				pos2 -= 1 / 10;

				nodes[i].moveToPosition(-pos2, -pos, baseDirection);
				nodes[i + 1].moveToPosition(pos2, -pos, baseDirection);
			}
		}
	}
	else {
		int halfNum = nodes.size() / 2;

		for (int i = 0; i < nodes.size(); i += 2) {
			pos = i / 10;//to change scaling change the divisor

			if (i <= halfNum) {
				nodes[i].moveToPosition(-pos, -pos, baseDirection);
				nodes[i + 1].moveToPosition(pos, -pos, baseDirection);

				pos2 = pos;
			}
			else {
				pos2 -= 1 / 10;

				nodes[i].moveToPosition(-pos2, -pos, baseDirection);
				nodes[i + 1].moveToPosition(pos2, -pos, baseDirection);
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
