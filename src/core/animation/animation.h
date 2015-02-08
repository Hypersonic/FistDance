#pragma once

struct Animation {
    int n_frames = 0;
    KeyFrame* keyframes;

    void apply(Skeleton& skeleton, double t);
};
