#pragma once

#include <cstring> // For size_t
#include <assert.h>

struct RigidBodyTransform {};
struct BodyInfo {};

struct SkeletonNode {
    
    SkeletonNode(RigidBodyTransform transform, BodyInfo info)
        : transform(transform), info(info) {}

    // Push returns this, so you can chain pushes
    SkeletonNode& push(int);

    size_t n_children = 0;
    int children[256];

    RigidBodyTransform transform;
    BodyInfo info;
};
