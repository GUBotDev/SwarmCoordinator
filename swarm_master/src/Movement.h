#pragma once

#include <cmath>
#include <array>
#include <vector>
#include "Parse.h"

class Movement {
public:
	void setFormation(int formation);
private:
	void invertedV();
	void xPattern();
	void diamond();
	std::vector<Node> nodes;
	float baseDirection;
};
