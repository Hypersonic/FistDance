#include "character.h"

Character::Character(double x, double y) {
	this->x = x;
	this->y = y;
	vx = 0;
	vy = 0;

    speed = 5;

	hitboxes.push_back(Hitbox(0, 0, 5));
	hitboxes.push_back(Hitbox(5, 5, 5));
}

void Character::render(SDL_Surface *drawSurface) {
	for (Hitbox& hb : hitboxes) {
		double x = this->x + hb.x;
		double y = this->y + hb.y;
        if (0 < x && x < drawSurface->w &&
            0 < y && y < drawSurface->h)
                fillCircle(drawSurface, x, y, hb.rad, hb.hit ? 0xff0000 : 0x0000ff);
	}
}

void Character::up(const bool pressed) {
	if (pressed) vy = -1;
	else if (vy < 0) vy = 0;
}

void Character::down(const bool pressed) {
	if (pressed) vy = 1;
	else if (vy > 0) vy = 0;
}

void Character::left(const bool pressed) {
	if (pressed) vx = -1;
	else if (vx < 0) vx = 0;
}

void Character::right(const bool pressed) {
	if (pressed) vx = 1;
	else if (vx > 0) vx = 0;
}
