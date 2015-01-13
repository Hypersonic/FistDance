#define MAC_OS_X_VERSION_MIN_REQUIRED 1050
#include <SDL2/SDL.h>
#include <stdio.h>
#include <dlfcn.h>
#include <sys/stat.h>

#include "core/core.h"

#define LIBNAME "FistDance_core.dylib"

int initSDL(int width, int height);

SDL_Window *window = NULL;
SDL_Surface *surface = NULL;

int main(int argc, char **argv) {
    void *lib; // A pointer to our library
    long libchanged; // Lib's timestamp last time we loaded it
    struct stat statbuf;
    GameState gamestate;
    char *err;

    // get the dll
    stat(LIBNAME, &statbuf);
    libchanged = statbuf.st_mtime;
    lib = dlopen(LIBNAME, RTLD_LOCAL);

	// initialize sdl
	if (initSDL(gamestate.canvasWidth, gamestate.canvasHeight) < 0) {
		printf("failed to init sdl: halting program");
		exit(1);
	}

    // Find and run our init function
    void (*init)(GameState&) = (void(*)(GameState&)) dlsym(lib, "init");
    if ((err = dlerror())) {
        printf("Error loading lib: %s\n", err);
        return -1;
    }
    init(gamestate);

    while (gamestate.running) {
        // Check for lib changes, reload if necessary
        stat(LIBNAME, &statbuf);
        if (statbuf.st_mtime != libchanged) {
            printf("Core lib has been changed, reloading");
            libchanged = statbuf.st_mtime;
            dlclose(lib);
            lib = dlopen(LIBNAME, RTLD_LOCAL);
        }

        // Find and run our step function
        void (*step)(GameState&) = (void(*)(GameState&))dlsym(lib, "step");
        if ((err = dlerror())) {
            printf("Error loading lib: %s\n", err);
            return -1;
        }
        step(gamestate);
    }

    dlclose(lib); // close the lib

	// wrap up SDL
	SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

int initSDL(int width, int height) {
	// init sdl
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Could not init SDL: %s", SDL_GetError());
	}

	window = SDL_CreateWindow("Fist Dance", SDL_WINDOWPOS_UNDEFINED,
	                          SDL_WINDOWPOS_UNDEFINED, width, height,
	                          SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Could not init window: %s", SDL_GetError());
	}
}
