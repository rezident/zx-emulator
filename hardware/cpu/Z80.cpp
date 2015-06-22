//
// Created by yuri on 21.06.15.
//

#include <iostream>
#include "Z80.h"

Z80::Z80(Memory *memory) {
    this->AF = new Register(0);
    this->BC = new Register(0);
    this->DE = new Register(0);
    this->HL = new Register(0);
    this->IX = new Register(0);
    this->IY = new Register(0);
    this->PC = new Register(0);
    this->SP = new Register(0);
    this->IR = new Register(0);

    this->interrupt = new Interrupt();
    this->frequency = new Frequency();
    this->memory = memory;

    this->init();

    this->thread = SDL_CreateThread(Z80::cpuThread, NULL, this);

    (this->*Z80::mainCommands[0xF3])();
}



int Z80::opt0xF3() {    // DI
    this->interrupt->setDisable();
    std::cout << "DI!!!";
    return 4;
}


int Z80::cpuThread(void *z80) {
    Z80 *cpu = (Z80 *) z80;

    return 0;
}
