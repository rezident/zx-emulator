//
// Created by yuri on 08.06.15.
//

#include "UsesINT.h"

void UsesINT::setINT() {
    this->comeINT = true;
}

void UsesINT::resetINT() {
    this->comeINT = false;
}

bool UsesINT::isComeINT() {
    return this->comeINT;
}
