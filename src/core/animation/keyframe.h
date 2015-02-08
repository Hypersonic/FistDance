#pragma once

#include "../skeleton/node.h"

struct KeyFrame {
    float frame; // The starting frame of the animation
    RigidBodyTransform trans;
};
