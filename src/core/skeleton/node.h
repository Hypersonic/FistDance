#pragma once

#include <cstring> // For size_t
#include <assert.h>

#include "../vec.h"

#define HTBX_HTBX 1
#define HTBX_FIST 3
#define HTBX_HTPT 0

struct RigidBodyTransform {
	Vec2 trans;
	double rot;
};

struct BodyInfo {
	int hittable;
	double rad;
};

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
