#ifndef FD_SDLU
#define FD_SDLU

#define MAC_OS_X_VERSION_MIN_REQUIRED 1050
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void putPixel(SDL_Surface *, int, int, Uint32);
void lockSurface(SDL_Surface *);
void unlockSurface(SDL_Surface *);
void fillRect(SDL_Surface *, double, double, double, double, Uint32);
void drawCircle(SDL_Surface *, double, double, double, Uint32);
void fillCircle(SDL_Surface *, double, double, double, Uint32);
void drawFont(SDL_Surface *, TTF_Font*, const double, const double, const char *, const Uint8 r, const Uint8 g, const Uint8 b); 

#endif
