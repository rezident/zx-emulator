#include <bits/stringfwd.h>
#include <stdexcept>
#include "INT.h"

SDL_Thread *INT::thread = SDL_CreateThread(INT::INTThread, NULL, NULL);
int INT::count = 0;
Frequency *INT::frequency = new Frequency();
UsesINT *INT::observers[MAX_INT_OBSERVERS];

void INT::addObserver(UsesINT *observer) {
    if(INT::count == MAX_INT_OBSERVERS) {
        throw std::runtime_error("Maximum of INT observers");
    }

    INT::observers[INT::count] = observer;
    INT::count++;
}

int INT::INTThread(void *pVoid) {
    while(true) {
        INT::frequency->wait(FREQUENCY / INT_PER_SECOND);
        for(int i = 0; i < INT::count; i++) {
            INT::observers[i]->setINT();
        }

    }

}
