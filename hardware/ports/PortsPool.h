//
// Created by yuri on 23.06.15.
//

#ifndef ZX_EMULATOR_PORTSPOOL_H
#define ZX_EMULATOR_PORTSPOOL_H


#include "PortWriter.h"
#include "PortReader.h"

class PortsPool {
public:
    /**
     * Инициализирует списки обработчиков пустыми значениями
     */
    static void init();
private:
    /**
     * Обработчики записи в порт
     */
    static PortWriter *writers[65536];

    /**
     * Обработчики чтения из порта
     */
    static PortReader *readers[65536];
};


#endif //ZX_EMULATOR_PORTSPOOL_H
