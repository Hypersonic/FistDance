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
    for (Character &ch : characters) {
        for (Hitbox& hb : ch.hitboxes) {
            hb.hit = false;
        }
    }
	//printf("simulation updating\n");
	for (Character &ch : characters) {
        if (ch.vx != 0 || ch.vy != 0) {
            auto len = sqrt(ch.vx * ch.vx + ch.vy * ch.vy);

            ch.x += ch.speed * ch.vx / len;
            if (checkCollisions(ch)) {
                ch.x -= ch.speed * ch.vx / len;
            }

            ch.y += ch.speed * ch.vy / len;
            if (checkCollisions(ch)) {
                ch.y -= ch.speed * ch.vy / len;
            }
        }
    }
}

bool Simulation::checkCollisions(Character& ch) {
    for (Character& other : characters) {
        if (&other == &ch) continue; // Skip checking against itself

        // For each pair of hitboxes, check circular collisions.
        // Return true if any of them collide
        for (Hitbox& char_hb : ch.hitboxes) {
            for (Hitbox& other_hb : other.hitboxes) {
                auto dhbx = (ch.x + char_hb.x) - (other.x + other_hb.x);
                auto dhby = (ch.y + char_hb.y) - (other.y + other_hb.y);

                auto radsum = char_hb.rad + other_hb.rad;
                if (sqrt(dhbx * dhbx + dhby * dhby) <= radsum) {
                    char_hb.hit = true;
                    other_hb.hit = true;
                    return true;
                }
            }
        }
    }
    return false;
}
