//
// Created by yuri on 21.06.15.
//

#include "Register.h"

Register::Register(doubleByte value) {
    this->setValue(value);
}

byte Register::getLow() {
    return this->low;
}

byte Register::getHigh() {
    return this->high;
}

doubleByte Register::getValue() {
    return this->value;
}

void Register::setValue(doubleByte value) {
    this->value = value;
    this->high = (byte) (value & 0b1111111100000000) >> 8;
    this->low = (byte) (value & 0b000000011111111);
}

void Register::setHigh(byte high) {
    this->high = high;
    this->highLowToValue();
}

void Register::setLow(byte Low) {
    this->low = low;
    this->highLowToValue();
}

void Register::highLowToValue() {
    this->value = (doubleByte) (this->high * 256 + this->low);
}
