#ifndef FD_UI
#define FD_UI

#define MAC_OS_X_VERSION_MIN_REQUIRED 1050
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <list>

#include "simulation.h"
#include "character.h"
#include "sdl_util.h"

#define MAX_LOG_SIZE 50


class UI {
	int canvasWidth;
	int canvasHeight;
	Simulation *sim;
    /* The following is a buffer for the DEBUG_TEXT macro to store it's stuff in. Do not use the DEBUG_TEXT macro outside of this class.
     * Do not look directly at the DEBUG_TEXT macro. Do not approach the DEBUG_TEXT macro. */
    char ui_debug_buffer[256];
    #define DEBUG_TEXT(fmt, stmt) (snprintf(ui_debug_buffer, sizeof(char) * sizeof(ui_debug_buffer), #stmt ":" fmt, stmt), ui_debug_buffer)
    std::list<char*> ui_debug_log;
public:
	SDL_Surface *drawSurface;
    TTF_Font *font;


	UI(Simulation& sim, int canvasWidth, int canvasHeight);
	void setSim(Simulation& sim);
	void render();

    void push_log_msg(char *msg);
};

#endif
