#include <bits/stringfwd.h>
#include <stdexcept>
#include "NMI.h"

SDL_Thread *NMI::thread = SDL_CreateThread(NMI::NMIThread, NULL, NULL);
int NMI::count = 0;
Frequency *NMI::frequency = new Frequency();
UsesNMI *NMI::observers[MAX_NMI_OBSERVERS];

void NMI::addObserver(UsesNMI *observer) {
    if(NMI::count == MAX_NMI_OBSERVERS) {
        throw std::runtime_error("Maximum of NMI observers");
    }

    NMI::observers[NMI::count] = observer;
    NMI::count++;
}

int NMI::NMIThread(void *pVoid) {
    while(true) {
        NMI::frequency->wait(FREQUENCY / NMI_PER_SECOND);
        for(int i = 0; i < NMI::count; i++) {
            NMI::observers[i]->setNMI();
        }

    }

}
