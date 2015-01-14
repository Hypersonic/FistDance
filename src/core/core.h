#ifndef DF_CORE
#define DF_CORE

#define MAC_OS_X_VERSION_MIN_REQUIRED 1050
#include <SDL2/SDL.h>
#include <stdio.h>

#include "simulation.h"
#include "ui.h"

#define CANVAS_WIDTH 1280
#define CANVAS_HEIGHT 720

// Disable name mangling because this is the interface
extern "C" {
    struct GameState {
        int canvasWidth = CANVAS_WIDTH;
        int canvasHeight = CANVAS_HEIGHT;
        bool running = true;
        Simulation* sim;
        UI* ui;
    };

    void init(GameState &);     // Called on first ever load
    void step(GameState &);     // Called each tick
    void load(GameState&);      // Called on every load
    void unload(GameState&);    // Called on every unload
    void terminate(GameState&); // Called on program close
}

void handleEvents(GameState &);
void keyDown(GameState &gamestate, SDL_Keycode code);
void keyUp(GameState &gamestate, SDL_Keycode code);

#endif
