#pragma once

#define MAC_OS_X_VERSION_MIN_REQUIRED 1050
#include <SDL2/SDL.h>
#include <vector>

#include "sdl_util.h"
#include "hitmasks.h"
#include "vec.h"
#include "skeleton/skeleton.h"

struct Hitbox {
	Vec2 pos;
    double rad;
    bool isFist;
    int hit = false;

    Hitbox(double x, double y, double rad, bool isFist) {
        pos = Vec2(x, y);
        this->rad = rad;
        this->isFist = isFist;
    }

    Hitbox(Vec2 pos, double rad, bool isFist) {
        this->pos = pos;
        this->rad = rad;
        this->isFist = isFist;
    }
};

class Character {
public:
    Vec2 pos;
    Vec2 ctrl_vel;
    Vec2 envt_vel;
    double speed;

    int jumpsLeft;
    int maxJumps;

    Skeleton skeleton;

    std::vector<Hitbox> hitboxes;

    Character(double, double);
    Character(Vec2);

    bool hittingPlatform();

    void render(SDL_Surface *drawSurface);
    void up(const bool);
    void down(const bool);
    void left(const bool);
    void right(const bool);
};
