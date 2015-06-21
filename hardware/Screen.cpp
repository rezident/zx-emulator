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
    INT::addObserver(this);
    this->setBorder(1);
    this->buildScreenMap();
    this->thread = SDL_CreateThread(Screen::updateScreenThread, NULL, this);

//    Uint32 *ppp;
//    ppp = (Uint32 *) this->surface->pixels + 50000;
//    *ppp = (Uint32) SDL_MapRGB(surface->format, 255, 0, 0); ppp++;
//    *ppp = (Uint32) SDL_MapRGB(surface->format, 255, 0, 0); ppp++;
//    *ppp = (Uint32) SDL_MapRGB(surface->format, 0, 255, 0); ppp++;
//    *ppp = (Uint32) SDL_MapRGB(surface->format, 255, 255, 0); ppp++;
//    SDL_UpdateWindowSurface(this->window);
}

int Screen::updateScreenThread(void *screen) {
//    exit(54);
    Screen *scr = (Screen *) screen;
    SDL_UpdateWindowSurface(scr->window);
    std::cout << scr << "asd";
    while(true) {
        while(!scr->isComeINT()) {}
        scr->resetINT();
        scr->flashHandler();
        scr->paint();
    }

    return 0;
}

void Screen::setBorder(byte border) {
    this->border = (byte) (border & 0b00000111);
    this->borderAttribute = (byte) (this->border | this->border << 3);
}

void Screen::initPalette() {
    this->palette[0] = (Uint32) SDL_MapRGB(this->surface->format, 0x00, 0x00, 0x00); // BLACK
    this->palette[1] = (Uint32) SDL_MapRGB(this->surface->format, 0x00, 0x00, 0xC0); // BLUE
    this->palette[2] = (Uint32) SDL_MapRGB(this->surface->format, 0xC0, 0x00, 0x00); // RED
    this->palette[3] = (Uint32) SDL_MapRGB(this->surface->format, 0xC0, 0x00, 0xC0); // MAGENTA
    this->palette[4] = (Uint32) SDL_MapRGB(this->surface->format, 0x00, 0xC0, 0x00); // GREEN
    this->palette[5] = (Uint32) SDL_MapRGB(this->surface->format, 0x00, 0xC0, 0xC0); // CYAN
    this->palette[6] = (Uint32) SDL_MapRGB(this->surface->format, 0xC0, 0xC0, 0x00); // YELLOW
    this->palette[7] = (Uint32) SDL_MapRGB(this->surface->format, 0xC0, 0xC0, 0xC0); // WHITE

    this->palette[8] = (Uint32) SDL_MapRGB(this->surface->format, 0x00, 0x00, 0x00); // BLACK
    this->palette[9] = (Uint32) SDL_MapRGB(this->surface->format, 0x00, 0x00, 0xFF); // BLUE
    this->palette[10] = (Uint32) SDL_MapRGB(this->surface->format, 0xFF, 0x00, 0x00); // RED
    this->palette[11] = (Uint32) SDL_MapRGB(this->surface->format, 0xFF, 0x00, 0xFF); // MAGENTA
    this->palette[12] = (Uint32) SDL_MapRGB(this->surface->format, 0x00, 0xFF, 0x00); // GREEN
    this->palette[13] = (Uint32) SDL_MapRGB(this->surface->format, 0x00, 0xFF, 0xFF); // CYAN
    this->palette[14] = (Uint32) SDL_MapRGB(this->surface->format, 0xFF, 0xFF, 0x00); // YELLOW
    this->palette[15] = (Uint32) SDL_MapRGB(this->surface->format, 0xFF, 0xFF, 0xFF); // WHITE
}

void Screen::flashHandler() {
    this->flashCounter++;
    if(this->flashCounter > FLASH_CHANGE_EVERY_INT) {
        this->flashCounter = 0;
        this->flashInverted = !this->flashInverted;
    }

}

void Screen::buildScreenMap() {
    int x, y;
    ScreenMapElement *map = (ScreenMapElement *) this->screenMap;

    byte *screenData = (byte *) this->memory->getPointer(16384);
    byte *screenAttributes = (byte *) this->memory->getPointer(16384 + 6144);
    Uint32 *win;
    win = (Uint32 *) this->surface->pixels;

    map->pointerWin = NULL;
    map->tactsWait = SYNCHRO_TOP_LINES * 4
                     * WINDOW_WIDTH_SYMBOLS
                     + (SYNCHRO_TOP_LINES * SYNCHRO_LEFT_TICKS) + SYNCHRO_LEFT_TICKS;
    map++;

    for(y = 0; y < BORDER_TOP_LINES; y++) {
        for(x = 0; x < WINDOW_WIDTH_SYMBOLS; x++) {
            this->buildScreenMapSymbol(
                    map, win, this->borderData, this->borderAttribute
            );
        }

        win = win + WINDOW_WIDTH * (SCREEN_SCALE - 1);
        (map-1)->tactsWait += SYNCHRO_LEFT_TICKS;
    }

    for(int third = 0; third < 3; third++) {
        for(int symbolY = 0; symbolY < 8; symbolY++) {
            for(y = 0; y < 8; y++) {
                for(x = 0; x < BORDER_LEFT_PIXELS / 8; x++) {
                    this->buildScreenMapSymbol(
                            map, win, this->borderData, this->borderAttribute
                    );
                }
                for(x = 0; x < SCREEN_X_SYMBOLS; x++) {
                    this->buildScreenMapSymbol(
                            map, win, *screenData, *screenAttributes
                    );
                    screenData++;
                    screenAttributes++;
                }

                screenData -= SCREEN_X_SYMBOLS;
                screenData += 8 * SCREEN_X_SYMBOLS;
                screenAttributes -= SCREEN_X_SYMBOLS;

                for(x = 0; x < BORDER_RIGHT_PIXELS / 8; x++) {
                    this->buildScreenMapSymbol(
                            map, win, this->borderData, this->borderAttribute
                    );
                }

                win = win + WINDOW_WIDTH * (SCREEN_SCALE - 1);
                (map-1)->tactsWait += SYNCHRO_LEFT_TICKS;
            }

            screenAttributes += SCREEN_X_SYMBOLS;
            screenData = screenData - 8 * 8 * SCREEN_X_SYMBOLS + SCREEN_X_SYMBOLS;
        }

        screenData = screenData + 7 * 8 * SCREEN_X_SYMBOLS;
    }

    for(y = 0; y < BORDER_BOTTOM_LINES; y++) {
        for(x = 0; x < WINDOW_WIDTH_SYMBOLS; x++) {
            this->buildScreenMapSymbol(
                    map, win, this->borderData, this->borderAttribute
            );
        }

        win = win + WINDOW_WIDTH * (SCREEN_SCALE - 1);
        (map-1)->tactsWait += SYNCHRO_LEFT_TICKS;
    }

}

void Screen::buildScreenMapSymbol(ScreenMapElement *&map, Uint32 *&win, byte &data, byte &attribute) {
    int x;
    byte dataMask = 0b10000000;
    for(x = 0; x < 8; x++) {
        this->buildScreenMapPixel(map, win, data, dataMask, attribute);
        dataMask = dataMask >> 1;
    }
}

void Screen::buildScreenMapPixel(ScreenMapElement *&map, Uint32 *&win, byte &data, byte dataMask, byte &attribute) {
    bool isFirstPixel = (dataMask == 0b10000000);
    bool isLastPixel = (dataMask == 0b00000001);
    for(int y = 0; y < SCREEN_SCALE; y++) {
        for(int x = 0; x < SCREEN_SCALE; x++) {
            map->pointerWin = win;
            map->usePreviousPixel = (x > 0 || y > 0);
            map->usePreviousAttribute = (x > 0 || y > 0 || !isFirstPixel);
            map->pointerData = &data;
            map->dataMask = dataMask;
            map->pointerAttribute = &attribute;
            map->tactsWait = ((x == y) && (y == (SCREEN_SCALE-1)) && isLastPixel) ? 4 : 0;
            map++;
            win++;
        }
        win = win - SCREEN_SCALE;
        win = win + WINDOW_WIDTH;
    }

    win = win - WINDOW_WIDTH * SCREEN_SCALE + SCREEN_SCALE;
}

void Screen::paint() {
    ScreenMapElement element;
    Uint32 *win;
    Uint32 paper = this->palette[0];
    Uint32 ink = this->palette[0];
    Uint32 pixel = this->palette[0];
    int bright;
    bool flash;

    for(int i = 0; i < WINDOW_WIDTH*WINDOW_HEIGHT+1; i++) {
        element = screenMap[i];
        if(element.pointerWin != NULL) {
            if(!element.usePreviousAttribute) {
                bright = (int) *element.pointerAttribute & 0b01000000 >> 3;
                flash = (*element.pointerAttribute & 0b10000000) == 0b10000000;
                ink = this->palette[((int) *element.pointerAttribute & 0b00000111) | bright];
                paper = this->palette[(((int) *element.pointerAttribute & 0b00111000) >> 3) | bright];
                if(flash && this->flashInverted) {
                    Uint32 col = ink;
                    ink = paper;
                    paper = col;
                }
            }

            if(!element.usePreviousPixel) {
                pixel = (*element.pointerData & element.dataMask) ? ink : paper;
            }


            win = element.pointerWin;
            *win = pixel;
//            exit(5);
        }

        if(element.tactsWait > 0) {
            this->frequency->wait(element.tactsWait);
        }
    }

    SDL_UpdateWindowSurface(this->window);

}

