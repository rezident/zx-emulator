#include <x86intrin.h>
#include <unistd.h>
#include <SDL_thread.h>
#include "Frequency.h"

uint64_t Frequency::ratio = 2400000000 / FREQUENCY;
SDL_Thread *Frequency::thread = SDL_CreateThread(Frequency::updateRatioThread, NULL, NULL);

int Frequency::updateRatioThread(void *) {
    uint64_t start;
    uint64_t end;
    while(true) {
        start = _rdtsc();
        sleep(1);
        end = _rdtsc();
        Frequency::ratio = (end-start) / FREQUENCY;
    }

}


