#ifndef FD_UI
#define FD_UI

#define MAC_OS_X_VERSION_MIN_REQUIRED 1050
#include <SDL2/SDL.h>

#include <stdio.h>
#include "simulation.h"

class UI {
	int canvasWidth;
	int canvasHeight;
	Simulation *sim;
public:
	UI(Simulation& sim, int canvasWidth, int canvasHeight);
	void setSim(Simulation& sim);
	void render();
};

#endif
