#pragma once

#include <cmath>
#include <array>
#include <vector>
#include <tuple>

class Calculation {
public:
	std::pair<float, float> multilateration(float* radius, float* x, float* y, int size);
	std::tuple<float, float, float, float> twoCircleLocate(float r1, float r2, float x1, float x2, float y1, float y2);
	//float determineAngle(float xCurrent, float yCurrent, float xPrevious, float yPrevious);
private:
	std::pair<float, float> findBarycenter(float* x, float* y, float* error);
	std::tuple<float, float, float> twoCircleIntersect(float r1, float r2, float x1, float x2, float y1, float y2);
};
