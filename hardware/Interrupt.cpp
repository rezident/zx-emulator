//
// Created by yuri on 21.06.15.
//

#include "Interrupt.h"

void Interrupt::setMode0() {
    this->mode = 0;
}

void Interrupt::setMode1() {
    this->mode = 1;
}

void Interrupt::setMode2() {
    this->mode = 2;
}

void Interrupt::setEnable() {
    this->disable = false;

}

void Interrupt::setDisable() {
    this->disable = true;
}
