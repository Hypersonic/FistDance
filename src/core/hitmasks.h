#pragma once

#define HITMASK_HITBOX 1
#define HITMASK_PLATFORM 2

#define HITTING_HITBOX(hit) ((hit) & HITMASK_HITBOX)
#define HITTING_PLATFORM(hit) ((hit) & HITMASK_PLATFORM)
