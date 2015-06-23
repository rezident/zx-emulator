//
// Created by yuri on 22.06.15.
//

#include <iostream>
#include "Flag.h"

Flag::Flag(Register *af) {
    this->af = af;
}

void Flag::setC() {
    this->af->setLow((byte) (this->af->getLow() | 0b00000001));
}

void Flag::resetC() {
    this->af->setLow((byte) (this->af->getLow() & 0b11111110));
}

bool Flag::isC() {
    return (this->af->getLow() & 0b00000001) != 0;
}

void Flag::setZ() {
    this->af->setLow((byte) (this->af->getLow() | 0b01000000));
}

void Flag::resetZ() {
    this->af->setLow((byte) (this->af->getLow() & 0b10111111));
}

bool Flag::isZ() {
    return (this->af->getLow() & 0b01000000) != 0;
}

void Flag::setS() {
    this->af->setLow((byte) (this->af->getLow() | 0b10000000));
}

void Flag::resetS() {
    this->af->setLow((byte) (this->af->getLow() & 0b01111111));
}

bool Flag::isS() {
    return (this->af->getLow() & 0b10000000) != 0;
}

void Flag::setPV() {
    this->af->setLow((byte) (this->af->getLow() | 0b00000100));
}

void Flag::resetPV() {
    this->af->setLow((byte) (this->af->getLow() & 0b11111011));
}

bool Flag::isPV() {
    return (this->af->getLow() & 0b00000100) != 0;
}

void Flag::setN() {
    this->af->setLow((byte) (this->af->getLow() | 0b00000010));
}

void Flag::resetN() {
    this->af->setLow((byte) (this->af->getLow() & 0b11111101));
}

bool Flag::isN() {
    return (this->af->getLow() & 0b00000010) != 0;
}

void Flag::setH() {
    this->af->setLow((byte) (this->af->getLow() | 0b00010000));
}

void Flag::resetH() {
    this->af->setLow((byte) (this->af->getLow() & 0b11101111));
}

bool Flag::isH() {
    return (this->af->getLow() & 0b00010000) != 0;
}

void Flag::parityCalc() {
    int units = 0;
    byte a = this->af->getHigh();
    units += (bool) (a & 0b10000000);
    units += (bool) (a & 0b01000000);
    units += (bool) (a & 0b00100000);
    units += (bool) (a & 0b00010000);
    units += (bool) (a & 0b00001000);
    units += (bool) (a & 0b00000100);
    units += (bool) (a & 0b00000010);
    units += (bool) (a & 0b00000001);
    if(units % 2 == 0) {
        this->setPV();
    } else {
        this->resetPV();
    }
}

void Flag::ZCalc(byte result) {
    this->ZCalc((doubleByte) result);
}

void Flag::ZCalc(doubleByte result) {
    if(result == 0) {
        this->setZ();
    } else {
        this->resetZ();
    }
}

void Flag::SCalc(doubleByte result) {
    if((result & 0b1000000000000000) == 0) {
        this->resetS();
    }  else {
        this->setS();
    }
}

void Flag::SCalc(byte result) {
    this->SCalc((doubleByte) (result * 256));
}

void Flag::VCalc(bool isAdd, byte oldValue, byte newValue) {
    if(isAdd) {
        if(oldValue >= 0x00 && oldValue <= 0x7F && newValue >= 0x80 && newValue <= 0xFF) {
            this->setPV();
        } else {
            this->resetPV();
        }
    } else {
        if(newValue >= 0x00 && newValue <= 0x7F && oldValue >= 0x80 && oldValue <= 0xFF) {
            this->setPV();
        } else {
            this->resetPV();
        }
    }
}

void Flag::CCalc(bool isAdd, doubleByte operand1, doubleByte operand2) {
    if(isAdd) {
        if((operand1 + operand2) > 65535) {
            this->setC();
        } else {
            this->resetC();
        }
    } else {
        if((operand1 - operand2) < 0) {
            this->setC();
        } else {
            this->resetC();
        }
    }
}

void Flag::CCalc(bool isAdd, byte operand1, byte operand2) {
    this->CCalc(isAdd, (doubleByte) (operand1 * 256), (doubleByte) (operand2 * 256));
}

void Flag::HCalc(bool isAdd, doubleByte operand1, doubleByte operand2) {
    operand1 = (doubleByte) (operand1 & 0b0000000011111111);
    if(isAdd) {
        if((operand1 + operand2) > 255) {
            this->setH();
        }  else {
            this->resetH();
        }
    } else {
        if((operand1 - operand2) < 0) {
            this->setH();
        } else {
            this->resetH();
        }
    }
}

void Flag::HCalc(bool isAdd, byte operand1, byte operand2) {
    operand1 = (byte) (operand1 & 0b00001111);
    if(isAdd) {
        if((operand1 + operand2) > 0b00001111) {
            this->setH();
        }  else {
            this->resetH();
        }
    } else {
        if((operand1 - operand2) < 0) {
            this->setH();
        } else {
            this->resetH();
        }
    }
}
