#include "character.h"

Character::Character(double x, double y) {
	this->x = x;
	this->y = y;
	vx = 0;
	vy = 0;

    jumpsRemaining = 2;

    speed = 5;

	hitboxes.push_back(Hitbox(0, 0, 5));
	hitboxes.push_back(Hitbox(5, 5, 5));
}

void Character::render(SDL_Surface *drawSurface) {
	for (Hitbox& hb : hitboxes) {
		double x = this->x + hb.x;
		double y = this->y + hb.y;
        if (0 < x && x < drawSurface->w &&
            0 < y && y < drawSurface->h) {
            Uint32 color = 0x0000ff;
            if (HITTING_HITBOX(hb.hit)) {
                color = 0xff0000;
            }
            if (HITTING_PLATFORM(hb.hit)) {
                color = 0x00ff00;
                jumpsRemaining = 2; // Reset jumps left to 2
            }
            fillCircle(drawSurface, x, y, hb.rad, color);
        }
	}
}

bool Character::hittingPlatform() {
    for (Hitbox& hb : hitboxes) {
        if (HITTING_PLATFORM(hb.hit))
            return true;
    }
    return false;
}

void Character::up(const bool pressed) {
    if (pressed && jumpsRemaining > 0) {
        jumpsRemaining--;
        vy = -3;
    }
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
