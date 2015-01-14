#ifndef FD_CHAR
#define FD_CHAR

#define MAC_OS_X_VERSION_MIN_REQUIRED 1050
#include <SDL2/SDL.h>
#include <vector>

struct Hitbox {
	double x;
	double y;
	double rad;
	Hitbox(double x, double y, double rad) {
		this->x = x;
		this->y = y;
		this->rad = rad;
	}
};

class Character {
public:
	double x;
	double y;
	double vx;
	double vy;
	std::vector<Hitbox> hitboxes;

	Character(double, double);

	void render(SDL_Surface *);
};

void up(Character&, const bool);
void down(Character&, const bool);
void left(Character&, const bool);
void right(Character&, const bool);

#endif
