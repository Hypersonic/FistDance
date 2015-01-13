#ifndef DF_CORE
#define DF_CORE

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

    void init(GameState&);
    void step(GameState&);
}

#endif
