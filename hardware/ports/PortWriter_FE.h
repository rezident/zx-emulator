//
// Created by yuri on 23.06.15.
//

#ifndef ZX_EMULATOR_PORTWRITER_FE_H
#define ZX_EMULATOR_PORTWRITER_FE_H


#include "PortWriter.h"
#include "../Screen.h"

class PortWriter_FE: public PortWriter {
public:
    PortWriter_FE(Screen *screen);

    void write(byte value);
private:
    Screen *screen;
};


#endif //ZX_EMULATOR_PORTWRITER_FE_H
