#include <stdio.h>
#include <dlfcn.h>
#include <sys/stat.h>

#include "core/core.h"

#define LIBNAME "FistDance_core.dylib"

int main() {
    void *lib; // A pointer to our library
    long libchanged; // Lib's timestamp last time we loaded it
    struct stat statbuf;
    GameState gamestate;
    char * err;

    stat(LIBNAME, &statbuf);
    libchanged = statbuf.st_mtime;

    lib = dlopen(LIBNAME, RTLD_LOCAL);
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
        void (*step)(GameState&) = (void(*)(GameState&)) dlsym(lib, "step");
        if ((err = dlerror())) {
            printf("Error loading lib: %s\n", err);
            return -1;
        }
        step(gamestate);
    }

    dlclose(lib);
    return 0;
}
