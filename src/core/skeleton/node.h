#pragma once

#include <cstring> // For size_t
#include <assert.h>

// TODO: Fill these in (and possibly move them to another file)
struct RigidBodyTransform {};
struct BodyInfo {};

struct SkeletonNode {
    SkeletonNode() {}
    SkeletonNode(int parent, RigidBodyTransform transform, BodyInfo info)
        : parent(parent), transform(transform), info(info) {}

    void push(int);

    // Indices of child nodes in the parent Skeleton's list
    size_t n_children = 0;
    int children[256]; 
    int parent;

    RigidBodyTransform transform;
    BodyInfo info;
};
