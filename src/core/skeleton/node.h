#pragma once

#include <cstring> // For size_t
#include <assert.h>

// TODO: Fill these in (and possibly move them to another file)
struct RigidBodyTransform {};
struct BodyInfo {};

struct SkeletonNode {
    
    SkeletonNode() {}
    SkeletonNode(RigidBodyTransform transform, BodyInfo info)
        : transform(transform), info(info) {}

    void push(int);

    size_t n_children = 0;
    int children[256]; // Indecies of child nodes in the parent Skeleton's list

    RigidBodyTransform transform;
    BodyInfo info;
};
