#include "simulation.h"

Simulation::Simulation() {
	characters.push_back(Character(100, 100));
}

void Simulation::update() {
	//printf("simulation updating\n");
	for (Character &character : characters) {
		character.x += character.vx;
		character.y += character.vy;
	}
}
