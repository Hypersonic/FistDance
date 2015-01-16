#ifndef DF_CORE
#define DF_CORE

#define MAC_OS_X_VERSION_MIN_REQUIRED 1050
#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#include "simulation.h"
#include "ui.h"

#define CANVAS_WIDTH 1280
#define CANVAS_HEIGHT 720

#define TICKS_PER_SEC 60
#define CLOCKS_PER_TICK (CLOCKS_PER_SEC / TICKS_PER_SEC)

// Disable name mangling because this is the interface
extern "C" {
    struct GameState {
        int canvasWidth = CANVAS_WIDTH;
        int canvasHeight = CANVAS_HEIGHT;
        bool running = true;
        clock_t prevStepTime; // Amount of CLOCKS_PER_SEC that the previous frame took
        Simulation* sim;
        UI* ui;
    };

    void init(GameState &);      // Called on first ever load
    void step(GameState &);      // Called each tick
    void load(GameState &);      // Called on every load
    void unload(GameState &);    // Called on every unload
    void terminate(GameState &); // Called on program close
}

void handleEvents(GameState &);
void keyDown(GameState &, SDL_Keycode);
void keyUp(GameState &, SDL_Keycode);

#endif
