#pragma once

#include <cmath>
#include <array>
#include <vector>
#include "FollowerNode.h"
#include "ControllerNode.h"

class Movement {
public:
	void setFormation(int formation, ControllerNode controller);
private:
	void invertedV(ControllerNode controller);
	void cross(ControllerNode controller);
	void square(ControllerNode controller);

};