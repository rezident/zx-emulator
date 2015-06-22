//
// Created by yuri on 22.06.15.
//

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

void Flag::setPO() {
    this->af->setLow((byte) (this->af->getLow() | 0b00000100));
}

void Flag::resetPO() {
    this->af->setLow((byte) (this->af->getLow() & 0b11111011));
}

bool Flag::isPO() {
    return (this->af->getLow() & 0b00000100) != 0;
}

