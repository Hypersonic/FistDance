#include "ui.h"

UI::UI(Simulation& sim) {
	this->sim = &sim;
}

void UI::setSim(Simulation& sim) {
	this->sim = &sim;
}

void UI::render() {
	printf("ui rendering\n");
}
