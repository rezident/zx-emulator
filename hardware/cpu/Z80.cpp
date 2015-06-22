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

}


int Z80::cpuThread(void *z80) {
    Z80 *cpu = (Z80 *) z80;
    cpu->process();
    return 0;
}

void Z80::process() {
    Z80Command commandMethod;
    int tacts;
    while(true) {
        byte code = this->memory->readN(this->PC->getValue());
        commandMethod = this->mainCommands[code];
        this->PC->inc();
        if(commandMethod == NULL) {
            std::cout << "Unknown code: " << "#" << std::uppercase << std::hex << (int) code << std::endl;
            throw;
        }

        tacts = (this->*Z80::mainCommands[code])();
        this->frequency->wait(tacts);

    }
}


int Z80::opt0xF3() {    // DI
    this->interrupt->setDisable();
    return 4;
}

int Z80::opt0xAF() {    // XOR A

    return 4;
}