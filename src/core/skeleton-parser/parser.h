#pragma once

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <cctype>

#include "../skeleton/node.h"
#include "../skeleton/skeleton.h"

namespace skel_parser {
	// parse skel file fn and creates skel
	void parse(char *, Skeleton *);
	bool split(int, char **);

	bool isBlank(char *);
}
