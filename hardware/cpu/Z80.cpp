//
// Created by yuri on 21.06.15.
//

#include <iostream>
#include "Z80.h"
#include "../ports/PortsPool.h"

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
    this->flag = new Flag(this->AF);

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
        commandMethod = this->getCommandMethod(this->mainCommands, "");
        tacts = (this->*commandMethod)();
        this->frequency->wait(tacts);
    }
}

Z80::Z80Command Z80::getCommandMethod(Z80::Z80Command *commandsSet, const char *prefix) {
    Z80Command commandMethod;
    byte code = this->memory->readN(this->PC->getValue());
    this->PC->inc();
    commandMethod = commandsSet[code];
    if(commandMethod == NULL) {
        std::cout << "Unknown code: " << "#" << prefix << std::uppercase << std::hex << (int) code << std::endl;
        throw;
    }

    return commandMethod;
}



int Z80::opt0xAF() {    // XOR A
    this->AF->setHigh(0);
    this->flag->resetC();
    this->flag->resetN();
    this->flag->parityCalc();
    this->flag->resetH();
    this->flag->ZCalc((byte) 0);
    this->flag->SCalc((byte) 0);
    return 4;
}

int Z80::opt0xF3() {    // DI
    this->interrupt->setDisable();
    return 4;
}

int Z80::opt0x11() {    // LD DE,NN
    this->DE->setValue(this->memory->readNN(this->PC->getValue()));
    this->PC->inc();
    this->PC->inc();
    return 10;
}

int Z80::opt0xC3() {    // JP NN
    this->PC->setValue(this->memory->readNN(this->PC->getValue()));
    return 10;
}

int Z80::opt0x47() {    // LD B,A
    this->BC->setHigh(this->AF->getHigh());
    return 4;
}

int Z80::opt0x3E() {
    this->AF->setHigh(this->memory->readN(this->PC->getValue()));
    this->PC->inc();
    return 7;
}

int Z80::opt0xD3() {
    byte port = this->memory->readN(this->PC->getValue());
    this->PC->inc();
    PortsPool::write(this->AF->getHigh(), port, this->AF->getHigh());
    return 11;
}

int Z80::opt0xED() {
    return (this->*this->getCommandMethod(this->extendedCommands, "ED"))();
}

int Z80::opt0xED47() {
    this->IR->setHigh(this->AF->getHigh());
    return 9;
}

int Z80::opt0x00() {
    return 4;
}

int Z80::opt0x62() {
    this->HL->setHigh(this->DE->getHigh());
    return 4;
}

int Z80::opt0x6B() {
    this->HL->setLow(this->DE->getLow());
    return 4;
}

int Z80::opt0x36() {
    byte value = this->memory->readN(this->PC->getValue());
    this->PC->inc();
    this->memory->writeN(this->HL->getValue(), value);
    return 10;
}

int Z80::opt0x2B() {
    this->HL->dec();
    return 6;
}

int Z80::opt0xBC() {
    this->cpN(this->HL->getHigh());
    return 4;
}

void Z80::cpN(byte operand) {
    byte a = this->AF->getHigh();
    byte result = a - operand;

    this->flag->CCalc(false, a, operand);
    this->flag->NCalc(false);
    this->flag->VCalc(false, a, operand);
    this->flag->HCalc(false, a, operand);
    this->flag->SCalc(result);
    this->flag->ZCalc(result);

}
