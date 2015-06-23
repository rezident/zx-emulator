//
// Created by yuri on 23.06.15.
//

#include "PortWriter_FE.h"

PortWriter_FE::PortWriter_FE(Screen *screen) {
    this->screen = screen;

}

void PortWriter_FE::write(byte value) {
    this->screen->setBorder((byte) (value & 0b00000111));
}
