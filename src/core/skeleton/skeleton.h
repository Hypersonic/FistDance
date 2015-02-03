#pragma once

#include <cstring> // For size_t
#include <assert.h>

#include "node.h"

struct Skeleton {
    size_t n_nodes;
    SkeletonNode nodes[32];
};
