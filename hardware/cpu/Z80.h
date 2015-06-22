//
// Created by yuri on 21.06.15.
//

#ifndef ZX_EMULATOR_Z80_H
#define ZX_EMULATOR_Z80_H


#include "../Register.h"

class Z80 {
public:
    Z80();
private:
    Register *AF;
    Register *BC;
    Register *DE;
    Register *HL;
    Register *IX;
    Register *IY;
    Register *PC;
    Register *SP;
    Register *IR;
};


#endif //ZX_EMULATOR_Z80_H
