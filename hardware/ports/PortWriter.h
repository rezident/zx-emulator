//
// Created by yuri on 23.06.15.
//

#ifndef ZX_EMULATOR_PORTWRITER_H
#define ZX_EMULATOR_PORTWRITER_H

#include "../Memory.h"

class PortWriter {
public:
    virtual void write(byte value) = 0;
};


#endif //ZX_EMULATOR_PORTWRITER_H
