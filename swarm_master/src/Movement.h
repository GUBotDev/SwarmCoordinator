#pragma once

#include <cmath>
#include <array>
#include <vector>

class Movement {
public:
	void setFormation(int formation, ControllerNode controller);
private:
	void invertedV(ControllerNode controller);
	void cross(ControllerNode controller);
	void diamond(ControllerNode controller);
};
