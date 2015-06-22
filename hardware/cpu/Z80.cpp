//
// Created by yuri on 21.06.15.
//

#include "Z80.h"

Z80::Z80() {
    this->AF = new Register(0);
    this->BC = new Register(0);
    this->DE = new Register(0);
    this->HL = new Register(0);
    this->IX = new Register(0);
    this->IY = new Register(0);
    this->PC = new Register(0);
    this->SP = new Register(0);
    this->IR = new Register(0);
}
