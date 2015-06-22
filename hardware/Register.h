//
// Created by yuri on 21.06.15.
//

#ifndef ZX_EMULATOR_REGISTER_H
#define ZX_EMULATOR_REGISTER_H


#include "Memory.h"

class Register {

public:
    Register(doubleByte value);

    /**
     * Устаналивает значение регистра
     */
    void setValue(doubleByte value);

    /**
     * Устанавливает старший байт регистра
     */
    void setHigh(byte high);

    /**
     * Устанавливает младший байт регистра
     */
    void setLow(byte Low);

    /**
     * Возвращает значение регистра
     */
    doubleByte getValue();

    /**
     * Возвращает старший байт регистра
     */
    byte getHigh();

    /**
     * Возвращает младший байт регистра
     */
    byte getLow();

private:

    /**
     * Старший байт
     */
    byte high;

    /**
     * Младший байт
     */
    byte low;

    /**
     * Содержимой
     */
    doubleByte value;

    /**
     * Выставляет значение регистра по старшему и младшему байтам
     */
    void highLowToValue();
};


#endif //ZX_EMULATOR_REGISTER_H
