#include "ui.h"

UI::UI(Simulation& sim, int canvasWidth, int canvasHeight) {
	this->sim = &sim;
	this->canvasWidth = canvasWidth;
	this->canvasHeight = canvasHeight;
	this->drawSurface = SDL_CreateRGBSurface(0, canvasWidth, canvasHeight,
	                                         32, 0, 0, 0, 0);
	if (this->drawSurface == NULL) {
		printf("CreateRGBSurface failed: %s\n", SDL_GetError());
		// TODO cause this to fail somehow
	}

    font = TTF_OpenFont("res/font.ttf", 16);
    if (font == NULL) {
        printf("Unable to load font!\n");
    }
}

void UI::setSim(Simulation& sim) {
	this->sim = &sim;
}

void UI::render() {
	//printf("ui rendering\n");

	// draw background
	lockSurface(drawSurface);
	for (int i = 0; i < canvasHeight; i++) {
		for (int j = 0; j < canvasWidth; j++) {
			Uint32 color = -(int)fmax(i % 0xff, j % 0xff) << 16;
			putPixel(drawSurface, j, i, color);
		}
	}
	unlockSurface(drawSurface);

	// draw characters
	for (Character &ch : sim->characters) {
		ch.render(drawSurface);

		// debug render
		char vy_str[256];
		snprintf(vy_str, sizeof(vy_str), "vy:%.1f", ch.vy);
		drawFont(drawSurface, font, ch.x + 10, ch.y - 20, vy_str,
		         0xff, 0xff, 0xff);
	}

	// draw platforms
	for (Platform &pf : sim->platforms) {
		fillRect(drawSurface, pf.x, pf.y, pf.w, pf.h, 0x0000ff);
	}
}
