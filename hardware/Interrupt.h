//
// Created by yuri on 21.06.15.
//

#ifndef ZX_EMULATOR_INTERRUPT_H
#define ZX_EMULATOR_INTERRUPT_H


#include "signals/int/UsesINT.h"

class Interrupt: public UsesINT {

public:
    /**
     * Устанавливает 0 режим прерываний
     */
    void setMode0();

    /**
     * Устанавливает 1 режим прерываний
     */
    void setMode1();

    /**
     * Устанавливает 2 режим прерываний
     */
    void setMode2();

    /**
     * Включает обработку прерываний
     */
    void setEnable();

    /**
     * Отключает обработку прерываний
     */
    void setDisable();

private:
    /**
     * Режим прерываний
     */
    int mode;

    /**
     * Отключены лы прерывания
     */
    bool disable;
};


#endif //ZX_EMULATOR_INTERRUPT_H
