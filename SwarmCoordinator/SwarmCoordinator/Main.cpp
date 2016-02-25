#include <iostream>
#include "Calculation.h"

//sample code - rm later
int main() {
	Calculation calcObj;
	std::pair<float, float> position;
	float degree;
	float radius[4] = { 1.4, 0.25, 1.75, 1.15 };
	float x[4] = { -1, 1, -1, 1 };//static x positions
	float y[4] = { 1, 1, -1, -1 };//static y positions

	position = calcObj.multilateration(radius, x, y, 3);

	degree = calcObj.determineAngle(position.first, position.second, 0, 0);//replace zeros with previous x/y values (static), maybe average previous 3

	std::cout << "X: " << position.first << " Y: " << position.second << " deg: " << degree << std::endl;

	return 0;
}
