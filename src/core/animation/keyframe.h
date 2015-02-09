#pragma once

#include "../skeleton/node.h"

struct KeyFrame {
    double frame; // The starting frame of the animation
    std::map<std::string, RigidBodyTransform> transformations;
};
