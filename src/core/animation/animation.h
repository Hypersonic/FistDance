#pragma once

#include "../skeleton/skeleton.h"
#include "keyframe.h"

struct Animation {
    int n_frames = 0;
    KeyFrame* keyframes;

    void apply(Skeleton& skeleton, double t);
};
