#include "simulation.h"

Simulation::Simulation() {
    characters.push_back(Character(100, 100));
    for (int i = 0; i < 5; i++) {
        Character* charlie = new Character(200 + i * 200, 100);
        charlie->ctrl_vel.x = rand() % 10;
        charlie->ctrl_vel.y = rand() % 10;
        charlie->speed = .5;
        characters.push_back(*charlie);
    }

    for (int i = 0; i < 5; i++) {
        platforms.push_back(Platform(175 + i * 200, 200, 50, 10));
    }

    platforms.push_back(Platform(100, 300, 1000, 30));
}

void Simulation::update() {
    for (Character &ch : characters) {
        for (Hitbox& hb : ch.hitboxes) {
            hb.hit = 0;
        }
    }

    for (Character &ch : characters) {
        updateCharacter(ch);
    }
}

void Simulation::updateCharacter(Character &ch) {
	// apply a bit of gravity
    ch.envt_vel.y += 0.3;

    // move and check for collisions
    auto total_vel = ch.envt_vel + ch.ctrl_vel;
    if (total_vel.x != 0 || total_vel.y != 0) {
        auto len = ch.ctrl_vel.len();

        // handle x-movement / collisions
        auto dx = ch.envt_vel.x;
        if (len > 0) dx += ch.speed * ch.ctrl_vel.x / len;
        ch.pos.x += dx;
        if (checkCollisions(ch)) {
            ch.pos.x -= dx;
        }

        // handle y-movement / collisions
        auto dy = ch.envt_vel.y;
        if (len > 0) dy += ch.speed * ch.ctrl_vel.y / len;
        ch.pos.y += dy;
        if (checkCollisions(ch)) {
            ch.pos.y -= dy;

            // we hit something - so we should stop
            ch.envt_vel.y = 0;
            ch.ctrl_vel.y = 0;
        }
    }

    // jump code
    bool hasLanded = false;
    for (Hitbox &hb : ch.hitboxes) {
        if (HITTING_PLATFORM(hb.hit)) {
            hasLanded = true;
        }
    }

    if (hasLanded) {
        // if we've landed, reset jumpsRemaining
        ch.jumpsLeft = ch.maxJumps;
    } else if (ch.jumpsLeft == ch.maxJumps) {
        // if off the floor, make sure we 'used' a jump
        ch.jumpsLeft--;
    }
}

bool Simulation::checkCollisions(Character& ch) {
    for (Character& other : characters) {
        if (&other == &ch) continue; // Skip checking against itself

        // For each pair of hitboxes, check circular collisions.
        // Return true if any of them collide
        for (Hitbox& char_hb : ch.hitboxes) {
            for (Hitbox& other_hb : other.hitboxes) {
                Vec2 hb_diff = (ch.pos + char_hb.pos) -
                               (other.pos + other_hb.pos);
                auto radsum = char_hb.rad + other_hb.rad;

                if (hb_diff.len() <= radsum) {
                    char_hb.hit |= HITMASK_HITBOX;
                    other_hb.hit |= HITMASK_HITBOX;
                    return true;
                }
            }
        }
    }

    for (Platform &pf : platforms) {
        for (Hitbox &char_hb : ch.hitboxes) {
            if (cphcbb(pf, char_hb, ch)) return true;
        }
    }

    return false;
}

// TODO: come up with better function name
// check platform hitbox collision: nearest point
bool Simulation::cphcnp(Platform &pf, Hitbox &hb, Character &ch) {
    // center of platform
    Vec2 pfCenter = pf.pos + pf.dim / 2;

	// get nearest point to platf center
    Vec2 posDiff = pfCenter - (hb.pos + ch.pos);
    posDiff.normalize(hb.rad);
    auto near_pos = ch.pos + hb.pos + posDiff;

    if (pf.pointInPlat(near_pos)) {
        hb.hit |= HITMASK_PLATFORM;
        return true;
    }

    return false;
}

// TODO: come up with better function name
// check platform hitbox collision: bounding box
bool Simulation::cphcbb(Platform &pf, Hitbox &hb, Character &ch) {
    Vec2 platCenter = pf.pos + pf.dim / 2;
    Vec2 hb_pos = ch.pos + hb.pos;
	Vec2 radsum = pf.dim / 2 + Vec2(hb.rad, hb.rad);

    bool horzIntersect = abs(platCenter.x - hb_pos.x) < radsum.x;
    bool vertIntersect = abs(platCenter.y - hb_pos.y) < radsum.y;
    bool intersection = horzIntersect && vertIntersect;

    if (intersection) hb.hit |= HITMASK_PLATFORM;

    return intersection;
}
