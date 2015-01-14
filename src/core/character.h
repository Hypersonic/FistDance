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
	double x;
	double y;
public:
	std::vector<Hitbox> hitboxes;

	Character(double, double);

	void render(SDL_Surface *);
};

#endif
