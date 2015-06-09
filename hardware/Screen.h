#define SYNCHRO_TOP_LINES       16
#define SYNCHRO_LEFT_TICKS      32
#define BORDER_TOP_LINES        64
#define BORDER_BOTTOM_LINES     48
#define BORDER_LEFT_PIXELS      72
#define BORDER_RIGHT_PIXELS     56

#define SCREEN_X_PIXELS         256
#define SCREEN_Y_LINES          192

#define SCREEN_SCALE 3

#ifndef ZX_EMULATOR_SCREEN_H
#define ZX_EMULATOR_SCREEN_H


#include <SDL_video.h>
#include "signals/int/UsesINT.h"
#include "Memory.h"

class Screen: public UsesINT {
public:
    Screen(Memory *memory);

private:
    Memory *memory;
    SDL_Window *window;
    SDL_Surface *surface;
};


#endif //ZX_EMULATOR_SCREEN_H
