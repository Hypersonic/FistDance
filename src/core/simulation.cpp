#include "simulation.h"

Simulation::Simulation() {
    characters.push_back(Character(true, 100, 100));
    for (int i = 0; i < 10; i++) {
        Character* charlie = new Character(false, 200 + i * 100, 100);
        charlie->vx = rand() % 10;
        charlie->vy = rand() % 10;
        charlie->speed = .5;
        characters.push_back(*charlie);
    }

    for (int i = 0; i < 10; i++) {
    	platforms.push_back(Platform(175 + i * 100, 200, 50, 10));
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

    for (Platform &pf : platforms) {
        // TODO do a bounding-box check first
        for (Hitbox &char_hb : ch.hitboxes) {
            // center of platform
            auto cx = pf.x + pf.w / 2;
            auto cy = pf.y + pf.h / 2;

            // character => platform vector
            auto dx = cx - (char_hb.x + ch.x);
            auto dy = cy - (char_hb.y + ch.y);

            // renormalize vector to hitbox's radius
            auto len = sqrt(dx * dx + dy * dy);
            dx *= char_hb.rad / len;
            dy *= char_hb.rad / len;
            auto near_x = ch.x + char_hb.x + dx;
            auto near_y = ch.y + char_hb.y + dy;

            if (pf.x <= near_x && near_x <= pf.x + pf.w &&
            	pf.y <= near_y && near_y <= pf.y + pf.h) {
            	char_hb.hit = true;
            	return true;
            }
        }
    }

    return false;
}
