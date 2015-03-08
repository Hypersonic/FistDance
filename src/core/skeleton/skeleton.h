#pragma once

#include <cstring> // For size_t
#include <assert.h>
#include <map>
#include <string>

#include "node.h"

struct Skeleton {
    size_t n_nodes = 0;
    SkeletonNode nodes[32];

	std::map<std::string, size_t> names;
};
