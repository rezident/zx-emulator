//
// Created by yuri on 23.06.15.
//

#include <stddef.h>
#include <iostream>
#include <iomanip>
#include "PortsPool.h"
PortWriter *PortsPool::writers[65536];
PortReader *PortsPool::readers[65536];

void PortsPool::init() {
    for(int i = 0; i < 65536; i++) {
        PortsPool::writers[i] = NULL;
        PortsPool::readers[i] = NULL;
    }

}

void PortsPool::addWriter(doubleByte address, PortWriter *writer) {
    PortsPool::writers[address] = writer;
}

void PortsPool::write(byte highByte, byte lowByte, byte value) {
    doubleByte address = (doubleByte) (highByte * 256 + lowByte);
    address = (doubleByte) (PortsPool::writers[address] != NULL) ? address : lowByte;
    if(PortsPool::writers[address] != NULL) {
        PortsPool::writers[address]->write(value);
    } else {
        std::cout << "No port writer (#" << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << (highByte * 256 + lowByte) << ")" << std::endl;
    }

}
