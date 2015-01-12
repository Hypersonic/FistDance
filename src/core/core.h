#ifndef DF_CORE
#define DF_CORE
#include "simulation.h"
#include "ui.h"

// Disable name mangling because this is the interface
extern "C" {
    struct GameState {
        bool running = true;
        Simulation* sim;
        UI* ui;
    };

    void init(GameState*);
    void step(GameState*);
}

#endif
