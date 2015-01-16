#ifndef FD_SIM
#define FD_SIM

#include <vector>
#include <math.h>
#include <stdio.h>

#include "character.h"

// Holds all world state, handles updating it
class Simulation {
public:
	std::vector<Character> characters;

	Simulation();

	void update();

	bool checkCollisions(Character&);
};

#endif
