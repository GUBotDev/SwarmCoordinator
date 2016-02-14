#include "Calculation.h"

std::pair<float, float> Calculation::multilateration(float* radius, float* x, float* y, int size) {
	//2D Multilateration - add 3D later (without removing 2d of course)
	const int length = size;
	int iterations = 0;
	std::tuple<float, float, float, float> temp;
	float* xOut = new float[length * length - length];
	float* yOut = new float[length * length - length];
	float* areaOut = new float[length * length - length];
	float* errorOut = new float[length * length - length];

	//n^2 - n times
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			if (i != j) {
				temp = twoCircleIntersect(radius[i], radius[j], x[i], x[j], y[i], y[j]);
				xOut[iterations] = std::get<0>(temp);
				yOut[iterations] = std::get<1>(temp);
				areaOut[iterations] = std::get<2>(temp);
				errorOut[iterations] = std::get<3>(temp);

				iterations++;
			}
		}
	}

	std::pair<float, float> barycenter = findBarycenter(xOut, yOut, errorOut, areaOut);

	delete[] xOut;
	delete[] yOut;
	delete[] areaOut;
	delete[] errorOut;

	return barycenter;
}

std::pair<float, float> Calculation::findBarycenter(float* x, float* y, float* error, float* area) {// more erroneous values affect less
	int sizeX = sizeof(x);
	int sizeY = sizeof(y);
	float xAvg = 0;
	float yAvg = 0;

	for (int i = 0; i < sizeX; i++) {
		xAvg += x[i] * (1 - error[i]);// *(1 / area[i]);
		yAvg += y[i] * (1 - error[i]);// *(1 / area[i]);
	}

	xAvg /= sizeX - 1;
	yAvg /= sizeY - 1;

	return{ xAvg, yAvg };
}

std::tuple<float, float, float, float> Calculation::twoCircleIntersect(float r1, float r2, float x1, float x2, float y1, float y2) {
	//bool checkIntersect = (r1 - r2) * (r1 - r2) <= (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) && (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= (r1 + r2) * (r1 + r2);//check intersection the hard way
	float baseX1 = x1;
	float baseX2 = x2;
	float baseY1 = y1;
	float baseY2 = y2;
	float newX1 = 0;
	float newX2 = (float)sqrt(abs(x1 - x2) * abs(x1 - x2) + abs(y1 - y1) * abs(y2 - y1));
	float newY1 = 0;
	float newY2 = 0;
	bool intersect = true;
	float dis, disToCen, fullLengthY, area, placementAngle, oppSide, adjacSide, centerX, centerY, error;

	//circle intersection at imaginary points, a degenerate point, or two distinct points
	dis = newX2; // distance is X2 in converted coordinates
	disToCen = ((dis * dis) - (r2 * r2) + (r1 * r1)) / (2 * dis); // distance from x1, y1 to radical line
	//float halfLengthY = (4 * (dis * dis) * (r1 * r1) - ((dis * dis) - (r2 * r2) + (r1 * r1)) * ((dis * dis) - (r2 * r2) + (r1 * r1))) / (4 * (dis * dis));
	fullLengthY = (1 / dis) * sqrt((-1 * dis + r2 - r1) * (-1 * dis - r2 + r1) * (-1 * dis + r2 + r1) * (dis + r2 + r1));
	area =
		((r2 * r2) * acos(((dis * dis) + (r2 * r2) - (r1 * r1)) / (2 * dis * r2))) +
		((r1 * r1) * acos(((dis * dis) + (r1 * r1) - (r2 * r2)) / (2 * dis * r1))) -
		(0.5 * sqrt((-1 * dis + r2 + r1) * (dis + r2 - r1) * (dis - r2 + r1) * (dis + r2 + r1)));

	//find xy offset of radical point
	placementAngle = atan2(y2 - y1, x2 - x1);
	oppSide = sin(placementAngle) / disToCen;

	if (x1 - x2 < 0) {
		adjacSide = sqrt((disToCen * disToCen) + (oppSide * oppSide)) * -1;
	}
	else if (x1 - x2 >= 0) {
		adjacSide = sqrt((disToCen * disToCen) + (oppSide * oppSide));
	}

	centerX = baseX1 + adjacSide;
	centerY = baseY1 + adjacSide;

	error = abs((newX2 - r2 - r1) / newX2); // percent error: 0 -> 1

	return std::make_tuple(centerX, centerY, area, error);// x/y location of center of radical line, area of union, and percent error
}

//direction of movement since last measurement
float Calculation::determineAngle(float xCurrent, float yCurrent, float xPrevious, float yPrevious) {
	float posX, posY, rad, degree;
	float piRadDeg = (180 / 3.14159265359);

	posX = xCurrent - xPrevious;
	posY = yCurrent - yPrevious;

	degree = atan2(posY, posX) * piRadDeg;

	if (degree < 0) {
		degree += 360;
	}

	return degree;
}
