#pragma once

#include <math.h>

class Vec2 {
public:
	double x;
	double y;

	Vec2(double x=0, double y=0) : x(x), y(y) {}
    Vec2(Vec2& that) : x(that.x), y(that.y) {}

	void normalize(double new_len) {
	    double len = sqrt(x * x + y * y);
	    x = x / len * new_len;
	    y = y / len * new_len;
	}

    Vec2& add(Vec2 &that) {
        return *(new Vec2(x + that.x, y + that.y));
    }

	Vec2& addToSelf(Vec2 &vec) {
	    x += vec.x;
	    y += vec.y;
        return *this;
	}

    void negate() {
        x = -x;
        y = -y;
    }

    double len() {
        return sqrt(x * x + y * y);
    }

    Vec2 operator+=(Vec2 &vec) {
        addToSelf(vec);
        return *this;
    }

    Vec2 operator-=(Vec2 &vec) {
        Vec2 res = vec;
        res.negate();
        res.addToSelf(*this);
        return res;
    }

    Vec2 operator*=(double val) {
        x *= val;
        y *= val;
        return *this;
    }

    Vec2 operator/=(double val) {
        x /= val;
        y /= val;
        return *this;
    }
};
