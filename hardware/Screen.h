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
#include "Frequency.h"

class Screen: public UsesINT {
public:
    Screen(Memory *memory);

    /**
     * Устанавливает цвет бордера
     */
    void setBorder(byte border);

private:

    /**
     * Память компьютера ZX
     */
    Memory *memory;

    /**
     * Окно, в котором размещается экран
     */
    SDL_Window *window;

    /**
     * Пиксельная карта экрана
     */
    SDL_Surface *surface;

    /**
     * Частотный генератор
     */
    Frequency *frequency;

    /**
     * Поток, в котором идет обновление экрана
     */
    SDL_Thread *thread;

    /**
     * Цвет Border
     */
    byte border;

    /**
     * Поток, обновляющий экран
     */
    static int updateScreenThread(void *screen);

    Uint32 palette[16];

    void initPalette();
};


#endif //ZX_EMULATOR_SCREEN_H
