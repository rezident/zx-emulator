#include <x86intrin.h>
#include <unistd.h>
#include <SDL_thread.h>
#include <stdexcept>
#include "Frequency.h"

uint64_t Frequency::ratio = 2400000000 / FREQUENCY;
SDL_Thread *Frequency::thread = SDL_CreateThread(Frequency::updateRatioThread, NULL, NULL);

Frequency::Frequency() {
    this->lastTact = _rdtsc();

}

void Frequency::wait(int z80Tacts) {
    uint64_t waitTact = this->lastTact + z80Tacts * this->ratio;
    while(_rdtsc() < waitTact) { }
    this->lastTact = _rdtsc();
}

int Frequency::updateRatioThread(void *) {
    if(SDL_HasRDTSC() == false) {
        throw std::runtime_error("Current CPU not support RDTSC");
    }

    uint64_t start;
    uint64_t end;
    while(true) {
        start = _rdtsc();
        sleep(1);
        end = _rdtsc();
        Frequency::ratio = (end-start) / FREQUENCY;
    }

}


