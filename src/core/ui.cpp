#include "ui.h"

UI::UI(Simulation& sim, int canvasWidth, int canvasHeight) {
    this->sim = &sim;
    this->canvasWidth = canvasWidth;
    this->canvasHeight = canvasHeight;
    this->drawSurface = SDL_CreateRGBSurface(0, canvasWidth, canvasHeight,
                                             32, 0, 0, 0, 0);
    if (this->drawSurface == NULL) {
        printf("CreateRGBSurface failed: %s\n", SDL_GetError());
    }

    font = TTF_OpenFont("res/font.ttf", 16);
    if (font == NULL) {
        printf("Unable to load font!\n");
    }
}

void UI::setSim(Simulation& sim) {
    this->sim = &sim;
}

void UI::render() {
    // draw background
    lockSurface(drawSurface);
    for (int i = 0; i < canvasHeight; i++) {
        for (int j = 0; j < canvasWidth; j++) {
            Uint32 color = -(int)fmax(i % 0xff, j % 0xff) << 16;
            putPixel(drawSurface, j, i, color);
        }
    }
    unlockSurface(drawSurface);

    // draw characters
    for (Character &ch : sim->characters) {
        ch.render(drawSurface);
    }

    // draw platforms
    for (Platform &pf : sim->platforms) {
        fillRect(drawSurface, pf.pos, pf.dim, 0x0000ff);
    }

    int y = 32;
    for (char *msg : ui_debug_log) {
        y += TTF_FontHeight(font);
        drawFont(drawSurface, font, 0, y, msg, 0xff, 0xff, 0xff);

    }
}

void UI::push_log_msg(char *msg) {
    if (ui_debug_log.size() > MAX_LOG_SIZE) {
        ui_debug_log.pop_front();
    }
    ui_debug_log.push_back(msg);
}
