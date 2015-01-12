#include <stdio.h>
#include "simulation.h"

int main() {
    printf("Hello, FistDance!\n");
    bool running = true;
	Simulation sim = Simulation();

    while (running) {
    	sim.update();
    }

    return 0;
}
