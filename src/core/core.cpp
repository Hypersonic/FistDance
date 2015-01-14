#include "core.h"

// Disable name mangling because this is the interface
extern "C" {
	void init(GameState &gamestate) {
		gamestate.sim = new Simulation();
		gamestate.ui = new UI(*gamestate.sim, gamestate.canvasWidth,
		                      gamestate.canvasHeight);
	}

	void step(GameState &gamestate) {
		handleEvents(gamestate);
		gamestate.sim->update();
		gamestate.ui->render();
	}

    void load(GameState& gamestate) {
        printf("Loading\n");
    }

    void unload(GameState& gamestate) {
        printf("Unloading\n");
    }

    void terminate(GameState& gamestate) {
        printf("Terminating\n");
    	delete gamestate.sim;
    	delete gamestate.ui;
    }

}

// TODO make this run in another thread
void handleEvents(GameState &gamestate) {
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            gamestate.running = false;
            return;
        } else if (e.type == SDL_KEYDOWN && !e.key.repeat) {
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    gamestate.running = false;
                    return;
            }
        }
    }
}
