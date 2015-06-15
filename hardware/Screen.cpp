//
// Created by yuri on 10.06.15.
//

#include <SDL_timer.h>
#include <iostream>
#include "Screen.h"
#include "signals/int/INT.h"

Screen::Screen(Memory *memory) {
    this->memory = memory;
    this->window = SDL_CreateWindow(
            "ZX-Emulator",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            WINDOW_WIDTH, WINDOW_HEIGHT, 0
    );
    this->surface = SDL_GetWindowSurface(this->window);
    this->initPalette();
    this->thread = SDL_CreateThread(Screen::updateScreenThread, NULL, this);
    INT::addObserver(this);
    this->setBorder(1);
    this->buildScreenMap();

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
    while(true) {
        while(!scr->isComeINT()) {}
        scr->resetINT();
        scr->flashHandler();
    }

    return 0;
}

void Screen::setBorder(byte border) {
    this->border = (byte) (border & 0b00000111);
    this->borderAttribute = (byte) (this->border | this->border << 3);
}

void Screen::initPalette() {
    this->palette[0] = SDL_MapRGB(this->surface->format, 0x00, 0x00, 0x00); // BLACK
    this->palette[1] = SDL_MapRGB(this->surface->format, 0x00, 0x00, 0xC0); // BLUE
    this->palette[2] = SDL_MapRGB(this->surface->format, 0xC0, 0x00, 0x00); // RED
    this->palette[3] = SDL_MapRGB(this->surface->format, 0xC0, 0x00, 0xC0); // MAGENTA
    this->palette[4] = SDL_MapRGB(this->surface->format, 0x00, 0xC0, 0x00); // GREEN
    this->palette[5] = SDL_MapRGB(this->surface->format, 0x00, 0xC0, 0xC0); // CYAN
    this->palette[6] = SDL_MapRGB(this->surface->format, 0xC0, 0xC0, 0x00); // YELLOW
    this->palette[7] = SDL_MapRGB(this->surface->format, 0xC0, 0xC0, 0xC0); // WHITE

    this->palette[8] = SDL_MapRGB(this->surface->format, 0x00, 0x00, 0x00); // BLACK
    this->palette[9] = SDL_MapRGB(this->surface->format, 0x00, 0x00, 0xFF); // BLUE
    this->palette[10] = SDL_MapRGB(this->surface->format, 0xFF, 0x00, 0x00); // RED
    this->palette[11] = SDL_MapRGB(this->surface->format, 0xFF, 0x00, 0xFF); // MAGENTA
    this->palette[12] = SDL_MapRGB(this->surface->format, 0x00, 0xFF, 0x00); // GREEN
    this->palette[13] = SDL_MapRGB(this->surface->format, 0x00, 0xFF, 0xFF); // CYAN
    this->palette[14] = SDL_MapRGB(this->surface->format, 0xFF, 0xFF, 0x00); // YELLOW
    this->palette[15] = SDL_MapRGB(this->surface->format, 0xFF, 0xFF, 0xFF); // WHITE
}

void Screen::flashHandler() {
    this->flashCounter++;
    if(this->flashCounter > FLASH_CHANGE_EVERY_INT) {
        this->flashCounter = 0;
        this->flashInverted = !this->flashInverted;
    }

}

void Screen::buildScreenMap() {
    ScreenMapElement *map = this->screenMap;
    map->pointerWin = NULL;
    map->tactsWait = SYNCHRO_TOP_LINES * 4 *
            (BORDER_LEFT_PIXELS / 8 + SCREEN_X_PIXELS / 8 + BORDER_RIGHT_PIXELS / 8)
            + (SYNCHRO_TOP_LINES * SYNCHRO_LEFT_TICKS);
}
