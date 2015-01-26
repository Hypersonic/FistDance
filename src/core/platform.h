#pragma once

#include "vec.h"

class Platform {
public:
	Vec2 pos;
	Vec2 dim;

    Platform(double, double, double, double);
	bool pointInPlat(Vec2);
};
