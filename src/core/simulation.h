#pragma once

#include <vector>
#include <math.h>
#include <stdio.h>

#include "character.h"
#include "platform.h"
#include "hitmasks.h"

// Holds all world state, handles updating it
class Simulation {
    void updateCharacter(Character &);
    bool cphcnp(Platform &, Hitbox &, Character &);
    bool cphcbb(Platform &, Hitbox &, Character &);
public:
    std::vector<Character> characters;
    std::vector<Platform> platforms;

    Simulation();

    void update();
    bool checkCollisions(Character&);
};
