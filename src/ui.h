#ifndef FD_UI
#define FD_UI
#include <stdio.h>
#include "simulation.h"

class UI {
	Simulation *sim;
public:
	UI(Simulation& sim);
	void setSim(Simulation& sim);
	void render();
};

#endif
