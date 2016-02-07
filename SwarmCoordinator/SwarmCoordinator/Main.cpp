#include <iostream>
#include "Calculation.h"

//sample code
int main() {
	Calculation calcObj;
	std::pair<float, float> position;
	float degree;
	float radius[3] = { 15, 5, 6 };
	float x[3] = { -10, 0, 10 };//static x positions
	float y[3] = { -10, 10, -10 };//static y positions

	position = calcObj.multilateration(radius, x, y, 3);

	degree = calcObj.determineAngle(position.first, position.second, 0, 0);//replace zeros with previous x/y values (static), maybe average previous 3

	std::cout << "X: " << position.first << " Y: " << position.second << " deg: " << degree << std::endl;

	return 0;
}
