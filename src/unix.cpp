#define MAC_OS_X_VERSION_MIN_REQUIRED 1050
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <dlfcn.h>
#include <sys/stat.h>

#include "core/core.h"

#define LIBNAME "FistDance_core.dylib"

int initSDL(int width, int height);
void copyToWindowSurface(SDL_Surface *);
void drawToWindow();

SDL_Window *window = NULL;
SDL_Renderer *windowRenderer = NULL;
SDL_Surface *windowSurface = NULL;
SDL_Texture *windowTexture = NULL;

int main(int argc, char **argv) {
    void *lib; // A pointer to our library
    long libchanged; // Lib's timestamp last time we loaded it
    struct stat statbuf;
    GameState gamestate;
    char *err;

    // callback functions
    void (*init)(GameState&);
    void (*load)(GameState&);
    void (*step)(GameState&);
    void (*unload)(GameState&);
    void (*terminate)(GameState&);

    // get the dll
    stat(LIBNAME, &statbuf);
    libchanged = statbuf.st_mtime;
    lib = dlopen(LIBNAME, RTLD_LOCAL);

	// initialize sdl
	if (initSDL(gamestate.canvasWidth, gamestate.canvasHeight) < 0) {
		printf("failed to init sdl: halting program\n");
		exit(1);
	}

    // Find and run our init function
    init = (void(*)(GameState&)) dlsym(lib, "init");
    load = (void(*)(GameState&)) dlsym(lib, "load");
    step = (void(*)(GameState&))dlsym(lib, "step");
    unload = (void(*)(GameState&))dlsym(lib, "unload");
    terminate = (void(*)(GameState&))dlsym(lib, "terminate");
    if ((err = dlerror())) {
        printf("Error loading lib: %s\n", err);
        return -1;
    }
    init(gamestate);
    load(gamestate);

    while (gamestate.running) {
        // Check for lib changes, reload if necessary
        stat(LIBNAME, &statbuf);
        if (statbuf.st_mtime != libchanged) {
            printf("Core lib has been changed, reloading\n");
            libchanged = statbuf.st_mtime;

            // Call our unload binding, then actually unload and reload
            unload(gamestate);
            dlclose(lib);
            lib = dlopen(LIBNAME, RTLD_LOCAL);

            // Refresh our bindings
            load = (void(*)(GameState&)) dlsym(lib, "load");
            step = (void(*)(GameState&))dlsym(lib, "step");
            unload = (void(*)(GameState&))dlsym(lib, "unload");
            terminate = (void(*)(GameState&))dlsym(lib, "terminate");

            // call our load binding
            load(gamestate);
        }

        step(gamestate);

        // Blit from ui.drawSurface to windowSurface
        copyToWindowSurface(gamestate.ui->drawSurface);
        drawToWindow();
    }

    // call unload and terminate
    unload(gamestate);
    terminate(gamestate);

    dlclose(lib); // close the lib

	// wrap up SDL
	SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

int initSDL(int width, int height) {
	// init sdl
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Couldn't init SDL: %s\n", SDL_GetError());
		return -1;
	}

	window = SDL_CreateWindow("Fist Dance", SDL_WINDOWPOS_UNDEFINED,
	                          SDL_WINDOWPOS_UNDEFINED, width, height,
	                          SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "Couldn't init window: %s\n", SDL_GetError());
		return -1;
	}

	windowRenderer = SDL_CreateRenderer(window, -1,
	                                    SDL_RENDERER_ACCELERATED |
	                                    SDL_RENDERER_PRESENTVSYNC);
    if (windowRenderer == NULL) {
		fprintf(stderr, "Couldn't init renderer: %s\n", SDL_GetError());
		return -1;
    }

	windowSurface = SDL_CreateRGBSurface(0, CANVAS_WIDTH, CANVAS_HEIGHT,
	                                     32, 0, 0, 0, 0);
	if (windowSurface == NULL) {
		fprintf(stderr, "Couldn't init surface: %s\n", SDL_GetError());
		return -1;
	}

    windowTexture = SDL_CreateTextureFromSurface(windowRenderer,
                                                 windowSurface);
    if (windowTexture == NULL) {
		fprintf(stderr, "Couldn't init texture: %s\n", SDL_GetError());
		return -1;
    }

    if (TTF_Init() == -1)  {
        printf("Unable to initialize SDL_ttf: %s \n", TTF_GetError());
    }

	return 0;
}

void copyToWindowSurface(SDL_Surface *surface) {
    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = CANVAS_WIDTH;
    srcRect.h = CANVAS_HEIGHT;
    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = CANVAS_WIDTH;
    destRect.h = CANVAS_HEIGHT;
    SDL_BlitSurface(surface, &srcRect, windowSurface, &destRect);
}

void drawToWindow() {
	SDL_UpdateTexture(windowTexture, NULL, windowSurface->pixels,
	                  windowSurface->pitch);
	SDL_RenderCopy(windowRenderer, windowTexture, NULL, NULL);
	SDL_RenderPresent(windowRenderer);
}
