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
            keyDown(gamestate, e.key.keysym.sym);
        } else if (e.type == SDL_KEYUP) {
             keyUp(gamestate, e.key.keysym.sym);
        }
    }
}

void keyDown(GameState &gamestate, SDL_Keycode code) {
    Character &ch = gamestate.sim->characters[0];
    switch (code) {
        case SDLK_ESCAPE:
            gamestate.running = false;
            return;
        case SDLK_w:
            up(ch, true);
            break;
        case SDLK_s:
            down(ch, true);
            break;
        case SDLK_a:
            left(ch, true);
            break;
        case SDLK_d:
            right(ch, true);
            break;
    }
}

void keyUp(GameState &gamestate, SDL_Keycode code) {
    Character &ch = gamestate.sim->characters[0];
    switch (code) {
        case SDLK_w:
            up(ch, false);
            break;
        case SDLK_s:
            down(ch, false);
            break;
        case SDLK_a:
            left(ch, false);
            break;
        case SDLK_d:
            right(ch, false);
            break;
    }
}
