//
// Created by yuri on 21.06.15.
//

#ifndef ZX_EMULATOR_Z80_H
#define ZX_EMULATOR_Z80_H


#include "../Register.h"
#include "../Interrupt.h"
#include "../Frequency.h"


class Z80 {
typedef int (Z80::*Z80Command)();
public:
    Z80(Memory *memory);

    Z80Command mainCommands[256];

private:
    int opt0xF3();      // DI
    void init() {
        this->mainCommands[0xF3] = &Z80::opt0xF3;
    }



    Register *AF;
    Register *BC;
    Register *DE;
    Register *HL;
    Register *IX;
    Register *IY;
    Register *PC;
    Register *SP;
    Register *IR;

    Interrupt *interrupt;
    Frequency *frequency;
    Memory *memory;
    SDL_Thread *thread;

    int cpuThread(void *);

};


#endif //ZX_EMULATOR_Z80_H
