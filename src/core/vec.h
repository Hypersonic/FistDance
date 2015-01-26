#pragma once

#include <math.h>

class Vec2 {
public:
	double x;
	double y;

	Vec2() : x(0), y(0) {}
	Vec2(double x, double y) : x(x), y(y) {}

	void normalize(double new_len) {
	    double len = sqrt(x * x + y * y);
	    x = x / len * new_len;
	    y = y / len * new_len;
	}

	void add(Vec2 &vec) {
	    x += vec.x;
	    y += vec.y;
	}

    // negate
    void negate() {
        x = -x;
        y = -y;
    }

    double len() {
        return sqrt(x * x + y * y);
    }

    Vec2 operator+(Vec2 vec) {
        Vec2 res = *this;
        res.add(vec);
        return res;
    }

    Vec2 operator-(Vec2 vec) {
        Vec2 res = vec;
        res.negate();
        res.add(*this);
        return res;
    }

    Vec2 operator*(double val) {
        Vec2 res = *this;
        res.x *= val;
        res.y *= val;
        return res;
    }

    Vec2 operator/(double val) {
        Vec2 res = *this;
        res.x /= val;
        res.y /= val;
        return res;
    }
};
