#include "ui.h"

UI::UI(Simulation& sim, int canvasWidth, int canvasHeight) {
	this->sim = &sim;
	this->canvasWidth = canvasWidth;
	this->canvasHeight = canvasHeight;
	this->drawSurface = SDL_CreateRGBSurface(0, canvasWidth, canvasHeight,
	                                         32, 0xff000000, 0x00ff0000,
	                                         0x0000ff00, 0x000000ff);
	if (this->drawSurface == NULL) {
		printf("CreateRGBSurface failed: %s\n", SDL_GetError());
		// TODO cause this to fail somehow
	}
}

void UI::setSim(Simulation& sim) {
	this->sim = &sim;
}

void UI::render() {
	//printf("ui rendering\n");

	lockSurface(drawSurface);

	for (int i = 0; i < canvasHeight; i++) {
		for (int j = 0; j < canvasWidth; j++) {
			Uint8 *pixel = (Uint8 *)drawSurface->pixels;
			pixel += (i * drawSurface->pitch) + (j * sizeof(Uint32));
			Uint32 color = j % 0xff << 24;
			*((Uint32 *)pixel) = color;
		}
	}
	unlockSurface(drawSurface);
}

void UI::lockSurface(SDL_Surface *surface) {
	if (SDL_MUSTLOCK(surface))
		SDL_LockSurface(surface);
}
void UI::unlockSurface(SDL_Surface *surface) {
	if (SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
}
