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
	bakeHitboxes(Vec2(0, 0), 0);
}

void Character::bakeHitboxes(Vec2 trans, int ni) {
	SkeletonNode &node = skeleton.nodes[ni];
	trans += node.transform.trans;

	if (node.info.hittable) {
		hitboxes.push_back(Hitbox(trans, node.info.rad,
	                          	  node.info.hittable & HTBX_FIST));
	}

	for (int i = 0; i < node.n_children; i++) {
		bakeHitboxes(trans, node.children[i]);
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

	renderNode(drawSurface, pos, 0);
}

void Character::renderNode(SDL_Surface *drawSurface, Vec2 n_pos, int ni) {
	SkeletonNode &node = skeleton.nodes[ni];
	n_pos += node.transform.trans;

	for (int i = 0; i < node.n_children; i++) {
		SkeletonNode &child = skeleton.nodes[node.children[i]];

		Vec2 p2(n_pos);
		p2 += child.transform.trans;

		drawLine(drawSurface, n_pos, p2, 0xffff00);
		renderNode(drawSurface, n_pos, node.children[i]);
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
