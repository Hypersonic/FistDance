#include "node.h"

SkeletonNode& SkeletonNode::push(int index) {
    assert(n_children < sizeof(children));

    children[n_children] = index;
    ++n_children;

    return *this;
}
