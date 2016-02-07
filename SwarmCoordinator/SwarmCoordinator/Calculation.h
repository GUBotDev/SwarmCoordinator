#pragma once

#include <cmath>
#include <array>
#include <vector>

class Calculation {
public:
	std::pair<float, float> multilateration(float* radius, float* x, float* y, int size);
	float determineAngle(float xCurrent, float yCurrent, float xPrevious, float yPrevious);
private:
	std::pair<float, float> findBarycenter(float* x, float* y, float* error, float* area);
	std::tuple<float, float, float, float> twoCircleIntersect(float r1, float r2, float x1, float x2, float y1, float y2);
};