#include "vec.h"

double Vec2::len() {
    return sqrt(x * x + y * y);
}

void Vec2::normalize(double newlen) {
    x = x / len() * newlen;
    y = y / len() * newlen;
}

Vec2 operator+(const Vec2 first, const Vec2 second) {
    Vec2 ret(first.x, first.y);
    ret.x += second.x;
    ret.y += second.y;
    return ret;
}

Vec2 operator+=(Vec2& first, Vec2& second) {
    first.x += second.x;
    first.y += second.y;
    return first;
}

Vec2 operator-(const Vec2 first, const Vec2 second) {
    Vec2 ret(first.x, first.y);
    ret.x -= second.x;
    ret.y -= second.y;
    return ret;
}

Vec2 operator-=(Vec2& first, Vec2& second) {
    first.x -= second.x;
    first.y -= second.y;
    return first;
}

Vec2 operator*(const Vec2 vec, double factor) {
    Vec2 ret(vec.x, vec.y);
    ret.x *= factor;
    ret.y *= factor;
    return ret;
}

Vec2 operator*=(Vec2& vec, double factor) {
    vec.x *= factor;
    vec.y *= factor;
    return vec;
}

Vec2 operator/(const Vec2 vec, double factor) {
    Vec2 ret(vec.x, vec.y);
    ret.x /= factor;
    ret.y /= factor;
    return ret;
}

Vec2 operator/=(Vec2& vec, double factor) {
    vec.x /= factor;
    vec.y /= factor;
    return vec;
}
