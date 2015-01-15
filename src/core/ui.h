#ifndef FD_UI
#define FD_UI

#define MAC_OS_X_VERSION_MIN_REQUIRED 1050
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "simulation.h"
#include "character.h"
#include "sdl_util.h"

class UI {
	int canvasWidth;
	int canvasHeight;
	Simulation *sim;
public:
	SDL_Surface *drawSurface;
    TTF_Font *font;

	UI(Simulation& sim, int canvasWidth, int canvasHeight);
	void setSim(Simulation& sim);
	void render();
};

#endif
