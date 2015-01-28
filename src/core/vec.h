#pragma once

#include <math.h>

class Vec2 {
public:
	double x;
	double y;
    Vec2() : x(0), y(0) {}
    Vec2(double x, double y) : x(x), y(y) {}

    double len() const;
    void normalize(double newlen);
};

Vec2 operator+(const Vec2&, const Vec2&);
Vec2 operator+=(Vec2&, Vec2&);

Vec2 operator-(const Vec2&, const Vec2&);
Vec2 operator-=(Vec2&, Vec2&);

Vec2 operator*(const Vec2&, double);
Vec2 operator*=(Vec2&, double);

Vec2 operator/(const Vec2&, double);
Vec2 operator/=(Vec2&, double);
