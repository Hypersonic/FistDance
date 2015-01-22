#ifndef FD_CHAR
#define FD_CHAR

#define MAC_OS_X_VERSION_MIN_REQUIRED 1050
#include <SDL2/SDL.h>
#include <vector>

#include "sdl_util.h"
#include "hitmasks.h"

struct Hitbox {
	double x;
	double y;
	double rad;
	int hit = false;
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
	double ctrl_vx; // control
	double ctrl_vy;
    double speed;
	double envt_vx; // environment
	double envt_vy;
    int jumpsRemaining;
	std::vector<Hitbox> hitboxes;

	Character(double, double);

    bool hittingPlatform();

	void render(SDL_Surface *drawSurface);
	void up(const bool);
	void down(const bool);
	void left(const bool);
	void right(const bool);
};

#endif
