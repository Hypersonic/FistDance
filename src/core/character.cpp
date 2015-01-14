#include "character.h"

Character::Character(double x, double y) {
	this->x = x;
	this->y = y;
	vx = 0;
	vy = 0;

	hitboxes.push_back(Hitbox(0, 0, 10));
}

void Character::render(SDL_Surface *drawSurface) {
	for (Hitbox& hb : hitboxes) {
		SDL_Rect hitboxRect;
		hitboxRect.x = x + hb.x - hb.rad;
		hitboxRect.y = y + hb.y - hb.rad;
		hitboxRect.w = hb.rad * 2;
		hitboxRect.h = hb.rad * 2;

		SDL_FillRect(drawSurface, &hitboxRect, 0x0000ff);
	}
}
