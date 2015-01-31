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

void drawLine(SDL_Surface *drawSurface, Vec2 p1, Vec2 d1, Uint32 col) {
	Vec2 pos1;
	Vec2 pos2;

	lockSurface(drawSurface);
	if (abs(v2.x - v1.x) > abs(v2.y - v1.y)) {
		if (v1.x < v2.x) {
			pos1 = p1;
			pos2 = p2;
		} else {
			pos1 = p2;
			pos2 = p1;
		}

		putPixel(drawSurface, pos1.x, pos1.y, color);

		double slope = (pos2.y - pos1.y) / (pos2.x - pos1.x);
		int curY = pos1.y;
		for (int x = pos1.x + 1; x <= pos2.x; x++) {
			double nextY = pos1.y + slope * (x - pos1.x);

			if (slope > 0 && nextY - curY > 0.5) curY++;
			else if (slope < 0 && nextY - curY < -0.5) curY--;

			putPixel(drawSurface, x, curY, color);
		}
	} else {
		if (v1.y < v2.y) {
			pos1 = v1;
			pos2 = v2;
		} else {
			pos1 = v2;
			pos2 = v1;
		}

		putPixel(drawSurface, pos1.x, pos1.y, color);

		double slope = (pos2.x - pos1.x) / (pos2.y - pos1.y);
		int curX = pos1.x;
		for (int y = pos1.y + 1; y <= pos2.y; y++) {
			double nextX = pos1.x + slope * (y - pos1.y);

			if (slope > 0 && nextX - curX > 0.5) curX++;
			else if (slope < 0 && nextX - curX < -0.5) curX--;

			putPixel(drawSurface, curX, y, color);
		}
	}

	unlockSurface(drawSurface);
}

void fillRect(SDL_Surface *drawSurface, Vec2 pos, Vec2 dim, Uint32 col) {
    SDL_Rect rect;
    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = dim.x;
    rect.h = dim.y;

    SDL_FillRect(drawSurface, &rect, col);
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

void wikiFillCircle(SDL_Surface *drawSurface,
                    double x0, double y0, double rad, Uint32 color) {
    lockSurface(drawSurface);
    for (double dy = 1; dy <= rad; dy += 1.) {
        double dx = sqrt(2 * rad * dy - dy * dy);
        int x = x0 - dx;

        for (; x <= x0 + dx; x++) {
            putPixel(drawSurface, x, y0 + rad - dy, color);
            putPixel(drawSurface, x, y0 - rad + dy, color);
        }
    }
    unlockSurface(drawSurface);
}

void fillCircle(SDL_Surface *drawSurface,
                double x0, double y0, double rad, Uint32 color) {
    wikiFillCircle(drawSurface, x0, y0, rad, color);
}

void drawFont(SDL_Surface * screen, TTF_Font* font,
              const double x, const double y, const char * text,
              const Uint8 r, const Uint8 g, const Uint8 b) { 
    SDL_Color sdl_color = {r, g, b, 0};
    SDL_Surface* text_surface = TTF_RenderText_Blended(font, text,
                                                       sdl_color); 
    SDL_Rect dest = {static_cast<int>(x),
                     static_cast<int>(y),
                     text_surface->w,
                     text_surface->h};
    SDL_BlitSurface(text_surface, NULL, screen, &dest);
    SDL_FreeSurface(text_surface);
}
