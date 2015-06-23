//
// Created by yuri on 23.06.15.
//

#include <stddef.h>
#include <iostream>
#include "PortsPool.h"
PortWriter *PortsPool::writers[65536];
PortReader *PortsPool::readers[65536];

void PortsPool::init() {
    for(int i = 0; i < 65536; i++) {
        PortsPool::writers[i] = NULL;
        PortsPool::readers[i] = NULL;
    }

}

