#include "simulation.h"

Simulation::Simulation() {
	characters.push_back(Character(100, 100));
}

void Simulation::update() {
	//printf("simulation updating\n");
	for (Character &character : characters) {
        auto len = sqrt(character.vx * character.vx + character.vy * character.vy);
        if (len > 0) {
            character.x += character.vx / len;
            character.y += character.vy / len;
        }
	}
}
