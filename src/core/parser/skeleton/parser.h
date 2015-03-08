#pragma once

#include <stdio.h>

#include "../util.h"
#include "../../skeleton/node.h"
#include "../../skeleton/skeleton.h"

// parse skel file fn and create skel
void skel_parse(char *, Skeleton &);
void name(Skeleton &, size_t, char *);
