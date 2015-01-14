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

void up(Character& character, const bool pressed) {
	if (pressed) character.vy = -1;
	else if (character.vy < 0) character.vy = 0;
}

void down(Character& character, const bool pressed) {
	if (pressed) character.vy = 1;
	else if (character.vy > 0) character.vy = 0;
}

void left(Character& character, const bool pressed) {
	if (pressed) character.vx = -1;
	else if (character.vx < 0) character.vx = 0;
}

void right(Character& character, const bool pressed) {
	if (pressed) character.vx = 1;
	else if (character.vx > 0) character.vx = 0;
}
