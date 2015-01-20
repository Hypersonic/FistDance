#ifndef FD_SIM
#define FD_SIM

#include <vector>
#include <math.h>
#include <stdio.h>

#include "character.h"
#include "platform.h"
#include "hitmasks.h"

// Holds all world state, handles updating it
class Simulation {
public:
	std::vector<Character> characters;
	std::vector<Platform> platforms;

	Simulation();

	void update();
	bool checkCollisions(Character&);
};

#endif
