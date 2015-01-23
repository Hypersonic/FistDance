#include "character.h"

Character::Character(double x, double y) {
	this->x = x;
	this->y = y;
	ctrl_vx = 0;
	ctrl_vy = 0;
	envt_vx = 0;
	envt_vy = 0;

    maxJumps = 2;
    jumpsRemaining = maxJumps;

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
                jumpsRemaining = maxJumps; // Reset jumps left to max
            } else if (jumpsRemaining > 1) {
                jumpsRemaining = 1;
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
        envt_vy = -6;
    }
}

void Character::down(const bool pressed) {}

void Character::left(const bool pressed) {
	if (pressed) ctrl_vx = -1;
	else if (ctrl_vx < 0) ctrl_vx = 0;
}

void Character::right(const bool pressed) {
	if (pressed) ctrl_vx = 1;
	else if (ctrl_vx > 0) ctrl_vx = 0;
}
