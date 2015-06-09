//
// Created by yuri on 09.06.15.
//

#include <stdio.h>
#include <stdexcept>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include "Memory.h"

Memory::Memory() {
    FILE *rom = fopen("software/roms/48.rom", "rb");
    if(rom == NULL) {
        std::cout << "Open ROM file error: " << strerror(errno) << std::endl;
        throw;
    }

    fread(this->memory, 1, 16384, rom);
    if(ferror(rom) > 0) {
        std::cout << "Read ROM file error: " << strerror(ferror(rom)) << std::endl;
        throw;
    }

    fclose(rom);
}

byte Memory::readN(doubleByte addr) {
    return this->memory[addr];
}

doubleByte Memory::readNN(doubleByte addr) {
    return (doubleByte) (this->memory[addr] + this->memory[addr+1] * 256);
}

void Memory::writeN(doubleByte addr, byte data) {
    if(addr > 16383) {
        this->memory[addr] = data;
    }

}

void Memory::writeNN(doubleByte addr, doubleByte data) {
    this->writeN(addr, (byte) (data & 0x00FF));
    this->writeN((doubleByte) (addr+1), (byte) ((data & 0xFF00) >> 8));
}
