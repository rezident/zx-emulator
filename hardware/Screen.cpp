//
// Created by yuri on 10.06.15.
//

#include <SDL_timer.h>
#include <SDL_hints.h>
#include <iostream>
#include "Screen.h"
#include "signals/int/INT.h"

Screen::Screen(Memory *memory) {
    this->memory = memory;
    this->window = SDL_CreateWindow(
            "ZX-Emulator",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            (BORDER_LEFT_PIXELS+SCREEN_X_PIXELS+BORDER_RIGHT_PIXELS)*SCREEN_SCALE,
            (BORDER_TOP_LINES+SCREEN_Y_LINES+BORDER_BOTTOM_LINES)*SCREEN_SCALE, 0
    );
    this->surface = SDL_GetWindowSurface(this->window);
    this->frequency = new Frequency();
    this->thread = SDL_CreateThread(Screen::updateScreenThread, NULL, this);
    INT::addObserver(this);

//    Uint32 *ppp;
//    ppp = (Uint32 *) this->surface->pixels + 50000;
//    *ppp = (Uint32) SDL_MapRGB(surface->format, 255, 0, 0); ppp++;
//    *ppp = (Uint32) SDL_MapRGB(surface->format, 255, 0, 0); ppp++;
//    *ppp = (Uint32) SDL_MapRGB(surface->format, 0, 255, 0); ppp++;
//    *ppp = (Uint32) SDL_MapRGB(surface->format, 255, 255, 0); ppp++;
//    SDL_UpdateWindowSurface(this->window);
}

int Screen::updateScreenThread(void *screen) {
    Screen *scr = (Screen *) screen;
    return 0;
}

void Screen::setBorder(byte border) {
    this->border = border;
}
