#pragma once

#include <math.h>

class Vec2 {
public:
	double x;
	double y;
    Vec2() : x(0), y(0) {}
    Vec2(double x, double y) : x(x), y(y) {}

    double len();
    void normalize(double newlen);
};

Vec2 operator+(Vec2 first, Vec2 second);
Vec2 operator+=(Vec2& first, Vec2& second);

Vec2 operator-(Vec2 first, Vec2 second);
Vec2 operator-=(Vec2& first, Vec2& second);

Vec2 operator*(Vec2 vec, double factor);
Vec2 operator*=(Vec2& vec, double factor);

Vec2 operator/(Vec2 vec, double factor);
Vec2 operator/=(Vec2& vec, double factor);
