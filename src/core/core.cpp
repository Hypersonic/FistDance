#include "core.h"
#include <stdio.h>

// Disable name mangling because this is the interface
extern "C" {
    void init(GameState& gamestate) {
        gamestate.sim = new Simulation();
        gamestate.ui = new UI(*gamestate.sim);
    }

    void step(GameState& gamestate) {
        gamestate.sim->update();
        gamestate.ui->render();
    }
}
