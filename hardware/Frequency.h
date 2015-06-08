/**
 * Частота процессора
 */
#define FREQUENCY 3500000

#include <stdint.h>
#include <SDL2/SDL.h>

#ifndef ZX_EMULATOR_FREQUENCY_H
#define ZX_EMULATOR_FREQUENCY_H

/**
 * Частота
 */
class Frequency {

private:
    /**
     * Отношение частоты текущего к эмулируемому процессору
     */
    static uint64_t ratio;

    /**
     * Поток, в котором постоянно пересчитывается отношение частот процессоров
     */
    static SDL_Thread *thread;

    /**
     * Пересчитывает отношение частот процессоров
     */
    static int updateRatioThread(void *);

};

#endif //ZX_EMULATOR_FREQUENCY_H

