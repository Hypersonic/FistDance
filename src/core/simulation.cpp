#include "simulation.h"

Simulation::Simulation() {
	characters.push_back(Character(100, 100));
    for (int i = 0; i < 10; i++) {
        Character* charlie = new Character(200 + i * 100, 100);
        charlie->vx = rand() % 10;
        charlie->vy = rand() % 10;
        charlie->speed = .5;
        characters.push_back(*charlie);
    }
}

void Simulation::update() {
	//printf("simulation updating\n");
	for (Character &character : characters) {
        auto len = sqrt(character.vx * character.vx + character.vy * character.vy);
        if (len > 0) {
            character.x += character.speed * character.vx / len;
            if (checkCollisions(character)) {
                character.x -= character.speed * character.vx / len;
            }
            character.y += character.speed * character.vy / len;
            if (checkCollisions(character)) {
                character.y -= character.speed * character.vy / len;
            }
        }
	}
}

bool Simulation::checkCollisions(const Character& character) {
    for (const Character& other : characters) {
        if (&other == &character) continue; // Skip checking against itself

        // For each pair of hitboxes, check circular collisions. Return true if any of them are true 
        for (const Hitbox& char_hb : character.hitboxes) {
            for (const Hitbox& other_hb : other.hitboxes) {

                auto dhbx = (character.x + char_hb.x) - (other.x + other_hb.x);
                auto dhby = (character.y + char_hb.y) - (other.y + other_hb.y);

                if (sqrt(dhbx * dhbx + dhby * dhby) <= (char_hb.rad + other_hb.rad)) {
                        return true;
                }

            }
        }

    }
    return false;
}
