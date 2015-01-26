#include "platform.h"

Platform::Platform(double x, double y, double w, double h) {
    this->pos = Vec2(x, y);
    this->dim = Vec2(w, h);
};

bool Platform::pointInPlat(Vec2 pt) {
	return pos.x <= pt.x && pt.x <= pos.x + dim.x &&
	       pos.y <= pt.y && pt.y <= pos.y + dim.y;
}
