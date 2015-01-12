#include <stdio.h>

#include "simulation.h"
#include "ui.h"

int main() {
	printf("Hello, FistDance!\n");
	bool running = true;
	Simulation sim = Simulation();
	UI ui = UI(sim);

	while (running) {
		sim.update();
		ui.render();
	}

	return 0;
}
