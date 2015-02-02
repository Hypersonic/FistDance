#pragma once

#include <stdio.h>
#include <cctype>

#include "../skeleton/node.h"
#include "../skeleton/skeleton.h"

namespace skel_parser {
	// parse skel file fn and creates skel
	void parse(char *, Skeleton &);
	bool split(FILE *, char **);

	bool isBlank(char *);
}
