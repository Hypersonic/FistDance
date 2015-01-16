#include "core.h"

// Disable name mangling because this is the interface
extern "C" {
	void init(GameState &gamestate) {
		gamestate.sim = new Simulation();
		gamestate.ui = new UI(*gamestate.sim, gamestate.canvasWidth,
		                      gamestate.canvasHeight);
	}

	void step(GameState &gamestate) {
        clock_t start_time = clock();
		handleEvents(gamestate);
		gamestate.sim->update();
		gamestate.ui->render();
        clock_t end_time = clock();
        gamestate.prevStepTime = end_time - start_time;

		// draw fps counter
        char fps_buff[16];
        snprintf(fps_buff, sizeof(fps_buff), "%.0f fps",
                 1 / ((float) gamestate.prevStepTime / CLOCKS_PER_SEC));
        drawFont(gamestate.ui->drawSurface, gamestate.ui->font, 10, 10,
                 fps_buff, 255, 255, 255);

		// sleep for rest of thingy
		clock_t endWait = start_time + CLOCKS_PER_TICK;
		while (clock() < endWait);
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
            ch.up(true);
            break;
        case SDLK_s:
            ch.down(true);
            break;
        case SDLK_a:
            ch.left(true);
            break;
        case SDLK_d:
            ch.right(true);
            break;
    }
}

void keyUp(GameState &gamestate, SDL_Keycode code) {
    Character &ch = gamestate.sim->characters[0];
    switch (code) {
        case SDLK_w:
            ch.up(false);
            break;
        case SDLK_s:
            ch.down(false);
            break;
        case SDLK_a:
            ch.left(false);
            break;
        case SDLK_d:
            ch.right(false);
            break;
    }
}
