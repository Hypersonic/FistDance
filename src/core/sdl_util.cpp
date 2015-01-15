#include "sdl_util.h"

void lockSurface(SDL_Surface *surface) {
	if (SDL_MUSTLOCK(surface))
		SDL_LockSurface(surface);
}

void unlockSurface(SDL_Surface *surface) {
	if (SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
}

void putPixel(SDL_Surface *drawSurface, int x, int y, Uint32 color) {
	Uint8 *pixel = (Uint8 *)drawSurface->pixels;
	pixel += (y * drawSurface->pitch) + (x * sizeof(Uint32));
	*((Uint32 *)pixel) = color;
}

void fillRect(SDL_Surface *drawSurface,
               double x, double y, double w, double h, Uint32 color) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_FillRect(drawSurface, &rect, color);
}

// draw circle using midpint circle algorithm
void drawCircle(SDL_Surface *drawSurface,
                double x0, double y0, double rad, Uint32 color) {
	int i_rad = (int) rad;
	int i_x0 = x0;
	int i_y0 = y0;

	// first point
	int x = i_rad;
	int y = 0;
	int radiusError = 1 - x;

	lockSurface(drawSurface);
	while (x > y) {
		putPixel(drawSurface, x + x0, y + y0, color);
		putPixel(drawSurface, y + x0, x + y0, color);
		putPixel(drawSurface, x + x0, -y + y0, color);
		putPixel(drawSurface, y + x0, -x + y0, color);
		putPixel(drawSurface, -x + x0, y + y0, color);
		putPixel(drawSurface, -y + x0, x + y0, color);
		putPixel(drawSurface, -x + x0, -y + y0, color);
		putPixel(drawSurface, -y + x0, -x + y0, color);

		y++;
		if (radiusError < 0) {
			radiusError += 2 * y + 1;
		} else {
			x--;
			radiusError += 2 * (y - x + 1);
		}
	}
	unlockSurface(drawSurface);
}

void fillCircle(SDL_Surface *drawSurface,
                double x0, double y0, double rad, Uint32 color) {}
