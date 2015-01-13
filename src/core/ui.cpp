#include "ui.h"

UI::UI(Simulation& sim, int canvasWidth, int canvasHeight) {
	this->sim = &sim;
	this->canvasWidth = canvasWidth;
	this->canvasHeight = canvasHeight;
}

void UI::setSim(Simulation& sim) {
	this->sim = &sim;
}

void UI::render() {
	printf("ui rendering\n");
}
