#include "character.h"

Character::Character(double x, double y) {
    pos = Vec2(x, y);
    ctrl_vel = Vec2(0, 0);
    envt_vel = Vec2(0, 0);

    maxJumps = 2;
    jumpsLeft = maxJumps;

    speed = 5;

	skel_parser::parse("res/skeletons/human.skel", skeleton);
	bakeHitboxes();
}

Character::Character(Vec2 pos) {
    this->pos = pos;
    ctrl_vel = Vec2(0, 0);
    envt_vel = Vec2(0, 0);

    maxJumps = 2;
    jumpsLeft = maxJumps;

    speed = 5;

	skel_parser::parse("res/skeletons/human.skel", skeleton);
	bakeHitboxes();
}

void Character::bakeHitboxes() {
	for (int i = 0; i < skeleton.n_nodes; i++) {
		SkeletonNode &node = skeleton.nodes[i];

		if (node.info.hittable) {
			hitboxes.push_back(Hitbox(node.transform.trans,
			                          node.info.rad,
			                          node.info.hittable & HTBX_FIST));
		}
	}
}

void Character::render(SDL_Surface *drawSurface) {
    for (Hitbox& hb : hitboxes) {
        // get render pos for hitbox
        Vec2 hb_pos(pos);
        hb_pos += hb.pos;

        // check window bounds
        if (0 < hb_pos.x && hb_pos.x < drawSurface->w &&
            0 < hb_pos.y && hb_pos.y < drawSurface->h) {
            // pick color based on hit state
            Uint32 color;
            if (HITTING_PLATFORM(hb.hit)) {
                color = 0x00ff00;
            } else if (HITTING_HITBOX(hb.hit)) {
                color = 0xff0000;
            } else {
                color = 0x0000ff;
            }

            fillCircle(drawSurface, hb_pos.x, hb_pos.y, hb.rad, color);
        }
    }

	renderNode(drawSurface, 0);
}

void Character::renderNode(SDL_Surface *drawSurface, int node_i) {
	SkeletonNode &node = skeleton.nodes[node_i];

	for (int i = 0; i < node.n_children; i++) {
		Vec2 p1(pos);
		p1 += node.transform.trans;
		Vec2 p2(pos);
		p2 += skeleton.nodes[node.children[i]].transform.trans;

		drawLine(drawSurface, p1, p2, 0xffff00);
	}
}

bool Character::hittingPlatform() {
    for (Hitbox& hb : hitboxes) {
        if (HITTING_PLATFORM(hb.hit))
            return true;
    }
    return false;
}

void Character::up(const bool pressed) {
    if (pressed && jumpsLeft > 0) {
        jumpsLeft--;
        envt_vel.y = -6;
    }
}

void Character::down(const bool pressed) {}

void Character::left(const bool pressed) {
    if (pressed) ctrl_vel.x = -1;
    else if (ctrl_vel.x < 0) ctrl_vel.x = 0;
}

void Character::right(const bool pressed) {
    if (pressed) ctrl_vel.x = 1;
    else if (ctrl_vel.x > 0) ctrl_vel.x = 0;
}
