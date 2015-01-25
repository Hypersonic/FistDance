#include "simulation.h"

Simulation::Simulation() {
    characters.push_back(Character(100, 100));
    for (int i = 0; i < 5; i++) {
        Character* charlie = new Character(200 + i * 200, 100);
        charlie->ctrl_vx = rand() % 10;
        charlie->ctrl_vy = rand() % 10;
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
    // move and check for collisions
    ch.envt_vy += 0.3; // Apply a bit of gravity
    auto vx = ch.envt_vx + ch.ctrl_vx;
    auto vy = ch.envt_vy + ch.ctrl_vy;
    if (vx != 0 || vy != 0) {
        auto len = sqrt(ch.ctrl_vx * ch.ctrl_vx +
                        ch.ctrl_vy * ch.ctrl_vy);

        // handle x-movement / collisions
        auto dx = ch.envt_vx;
        if (len > 0) dx += ch.speed * ch.ctrl_vx / len;
        ch.x += dx;
        if (checkCollisions(ch)) {
            ch.x -= dx;
        }

        // handle y-movement / collisions
        auto dy = ch.envt_vy;
        if (len > 0) dy += ch.speed * ch.ctrl_vy / len;
        ch.y += dy;
        if (checkCollisions(ch)) {
            ch.y -= dy;

            // we hit something - so we should stop
            ch.envt_vy = 0;
            ch.ctrl_vy = 0;
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
                auto dhbx = (ch.x + char_hb.x) - (other.x + other_hb.x);
                auto dhby = (ch.y + char_hb.y) - (other.y + other_hb.y);

                auto radsum = char_hb.rad + other_hb.rad;
                if (sqrt(dhbx * dhbx + dhby * dhby) <= radsum) {
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
    auto cx = pf.x + pf.w / 2;
    auto cy = pf.y + pf.h / 2;

    // get vector from character to platform
    auto dx = cx - (hb.x + ch.x);
    auto dy = cy - (hb.y + ch.y);

    // renormalize vector to hitbox's radius
    auto len = sqrt(dx * dx + dy * dy);
    dx *= hb.rad / len;
    dy *= hb.rad / len;
    auto near_x = ch.x + hb.x + dx; // nearest point to platf center
    auto near_y = ch.y + hb.y + dy;

    if (pf.x <= near_x && near_x <= pf.x + pf.w &&
        pf.y <= near_y && near_y <= pf.y + pf.h) {
        hb.hit |= HITMASK_PLATFORM;
        return true;
    }

    return false;
}

// TODO: come up with better function name
// check platform hitbox collision: bounding box
bool Simulation::cphcbb(Platform &pf, Hitbox &hb, Character &ch) {
    auto pfcx = pf.x + pf.w / 2;
    auto pfcy = pf.y + pf.h / 2;

    bool horzIntersect = abs(pfcx - (ch.x + hb.x)) < pf.w / 2 + hb.rad;
    bool vertIntersect = abs(pfcy - (ch.y + hb.y)) < pf.h / 2 + hb.rad;
    bool intersection = horzIntersect && vertIntersect;

    if (intersection) hb.hit |= HITMASK_PLATFORM;

    return intersection;
}
