//
// Created by yuri on 08.06.15.
//

#include "UsesNMI.h"

void UsesNMI::setNMI() {
    this->comeNMI = true;
}

void UsesNMI::resetNMI() {
    this->comeNMI = false;
}

bool UsesNMI::isComeNMI() {
    return this->comeNMI;
}
